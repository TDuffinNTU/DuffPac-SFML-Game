#include "GameScene.h"
#include "DEFINITIONS.h"

#include <math.h>
#include <fstream>

namespace Toolbox 
{
	GameScene::GameScene(Game* game) 
	{
		// Set game pointer
		gameptr = game;

		// Load bg
		gameptr->LoadTexture("DEFAULTBG", "Sprites/Default.png");
		bg.setTexture(gameptr->GetTexture("DEFAULTBG"));

		// Load button textures
		gameptr->LoadTexture("RETURNBUTTON", "Sprites/MenuButton.png");
		gameptr->LoadTexture("RESTARTBUTTON", "Sprites/RestartButton.png");

		// Set button textures
		btn_return.setTexture(gameptr->GetTexture("RETURNBUTTON"));
		btn_restart.setTexture(gameptr->GetTexture("RESTARTBUTTON"));
		btn_restart.setPosition(300, 10);
		btn_return.setPosition(10, 10);

		// Load font
		gameptr->LoadFont("FONT", "Fonts/consolab.ttf");

		// Header text
		txt_header.setFont(gameptr->GetFont("FONT"));
		txt_header.setCharacterSize(80);
		txt_header.setString("3");

		// Score Text
		txt_score.setFont(gameptr->GetFont("FONT"));		
		txt_score.setCharacterSize(20);
		txt_score.setPosition(40, 50);

		// Hi_score Text
		txt_hi_score.setFont(gameptr->GetFont("FONT"));
		txt_hi_score.setCharacterSize(20);
		hi_score = Highscore(false);
		txt_hi_score.setString("HIGH SCORE: " + std::to_string(hi_score));
		txt_hi_score.setPosition(200, 50);		

		// Centre Header text
		sf::FloatRect textRect = txt_header.getLocalBounds();
		txt_header.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		txt_header.setPosition(sf::Vector2f(WIDTH / 2.0f, 40));

		// Load Game textures
		gameptr->LoadTexture("PLAYER", "Sprites/Player.png");
		gameptr->LoadTexture("WALL", "Sprites/Wall.png");
		gameptr->LoadTexture("ENEMY", "Sprites/Enemy.png");
		gameptr->LoadTexture("COIN", "Sprites/Coin.png");

		// Set grid size/offset
		grid_size = gameptr->GetTexture("WALL").getSize().x;
		grid_offset = sf::Vector2f(30, 80);

		// Load the player at the start pos
		LoadLevel();
		player = new Mobiles::Player(grid_offset, grid_size, player_start_pos, 
			gameptr->GetTexture("PLAYER"));
	}

	void GameScene::Input() 
	{
		sf::Event event;
		// Event loop for handling input
		while (gameptr->window.pollEvent(event))
		{
			switch (event.type)
			{
			// Close window event
			case sf::Event::Closed:
				gameptr->window.close();
				break;
			// If Esc is pressed return to main
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
				{
					gameptr->PopScene();
					return;
				}
				break;
			// Check for button clicks when LMB is pressed
			case sf::Event::MouseButtonPressed:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
				{
					CheckClicked();
					return; // Return called to end the loop, in case scene changes
				}					
				break;
			}
		}	
	}

	void GameScene::Update(const float dt) 
	{
		if (!started) 
		{
			// Countdown before game start
			if (clock.getElapsedTime().asSeconds() < READYTIME)
			{
				countdown = READYTIME - clock.getElapsedTime().asSeconds() + 1;
				txt_header.setString(std::to_string(countdown));
			}
			else 
			// Game has started, set started flag to true
			{
				started = true;
				txt_header.setString(" ");
				clock.restart();
			}
		}

		// Player has lost the game
		else if (player->dead) 
		{
			// Display "Game OVer" for a few seconds, then swap to
			if (game_over_clock.getElapsedTime().asSeconds() < GAMEOVERDISPLAY)
			{
			// Blink the "Game Over" text
				if (clock.getElapsedTime().asSeconds() > GAMEOVERBLINK)
				{
					clock.restart();
					if (!blink) {
						// Blink the text ON
						blink = !blink;
						txt_header.setString("GAME OVER");

						// Centre the text
						txt_header.setCharacterSize(40);
						sf::FloatRect textRect = txt_header.getLocalBounds();
						txt_header.setOrigin(textRect.left + textRect.width / 2.0f,
							textRect.top + textRect.height / 2.0f);
						txt_header.setPosition(sf::Vector2f(WIDTH / 2.0f, 30));
					}
					else 
					{
						// Blink the text OFF
						blink = !blink;
						txt_header.setString(" ");
					}
				}
			}
			// Game Over isn't being display, show the score!
			else 
			{
				// Ask to retry
				txt_header.setString("RETRY?");
				txt_header.setCharacterSize(40);
				sf::FloatRect textRect = txt_header.getLocalBounds();
				txt_header.setOrigin(textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);
				txt_header.setPosition(sf::Vector2f(WIDTH / 2.0f, 30));
				
				// If player has a new high score, show the player!
				if (new_hi_score)
				{
					txt_hi_score.setString("*NEW* HISCORE: " + std::to_string(score));
				}

				// Display the restart/return buttons
				show_end_buttons = true;
			}
		}

		// Game is playing normally
		else 
		{
			if (clock.getElapsedTime().asSeconds() > TICK) 
			{
				// Run the tick function only during certain intervals
				Tick();
			}
			// Input taken every frame, movement only during Tick cycles
			player->Input();	

			// Add some score few frames
			if (clock.getElapsedTime().asSeconds() > TIMESCORETICK) 
			{
				score += SCORETICK;
				txt_score.setString("SCORE: " + std::to_string(score));
			}
		}
	}

	void GameScene::Tick() 
	{
		// restart the tick clock, add some score
		clock.restart();

		// Check for collisions, move enemies
		// Checking collisions twice per loop to "fix" broken collisions when more sprites are on-screen
		for (uint16_t i = 0; i < enemies.size(); i++) 
		{
			enemies[i]->AutoInput(rand_clock.getElapsedTime().asMicroseconds());
			enemies[i]->CheckCollision(walls);
			enemies[i]->CheckCollision(walls);
			enemies[i]->Update();
		}

		// Check for collisions, move player
		player->CheckCollision(walls);
		player->CheckCollision(walls);
		
		int coin_touched = player->CoinCollision(coins);
		if (coin_touched != -1) 
		{
			score += coins[coin_touched]->score;
			coins.erase(coins.begin() + coin_touched );	
			txt_score.setString("SCORE: " + std::to_string(score));
		}

		// Check for enemy collisions
		player->EnemyCollision(enemies);

		// Player has died during this tick; dont move 'em and perform end-of-game tasks
		if (player->dead) 
		{
			game_over_clock.restart();
			if (score > hi_score) 
			{
				printf("NEW HIGH SCORE: %i, OLD: %i\n", score, hi_score);
				new_hi_score = true;
				Highscore(true);
			}
			return;
		}
		player->Update();	
	}

	void GameScene::Draw(const float dt) 
	// Draw the scene
	{
		// Draw the background
		gameptr->window.draw(bg);
		// Only draw the countdown timer if the level hasnt started yet
		if (!started || player->dead)
			gameptr->window.draw(txt_header);
		
		// Draw score text only if game is running
		if (started) 
		{
			gameptr->window.draw(txt_score);
			gameptr->window.draw(txt_hi_score);
		}

		// Draw the buttons/player
		gameptr->window.draw(player->sprite);

		// Draw the buttons only if game has ended
		if (show_end_buttons) 
		{
			gameptr->window.draw(btn_return);
			gameptr->window.draw(btn_restart);
		}

		// Draw all coins
		for (uint16_t i = 0; i < coins.size(); i++)
		{
			gameptr->window.draw(coins[i]->sprite);
		}

		// Draw all enemies
		for (uint16_t i = 0; i < enemies.size(); i++)
		{
			gameptr->window.draw(enemies[i]->sprite);
		}

		// Draw all of the walls
		for (uint16_t i = 0; i < walls.size(); i++) 
		{
			gameptr->window.draw(walls[i]->sprite);
		}
	}

	void GameScene::CheckClicked() 
	// Checks to see if any button has been clicked
	{
		if (gameptr->SpriteClicked(btn_return))
		{			
			gameptr->PopScene();
			return;
		}
		if (gameptr->SpriteClicked(btn_restart)) 
		{ 
			gameptr->SwapScene(new GameScene(gameptr)); 
			return;
		}
	}

	void GameScene::LoadLevel() 
	// Loads the level into the scene from a txt file
	{
		// Opens the map file to be loaded
		std::ifstream map_file;
		map_file.open("Levels/MAP.txt");

		if (map_file.is_open()) 
		{
			// Variables X and Y track positions
			int y = 0;
			for (std::string line; std::getline(map_file, line);) 
			{
				int x = 0;
				for (char& ch : line) 
				{
					switch (ch) 
					{
					case '#':
						// Place walls at positions denoted by "#"
						walls.push_back(new Obstacles::Wall(grid_offset, grid_size, 
							sf::Vector2f(x, y), gameptr->GetTexture("WALL")));
						//printf("NEW Wall: %i, %i\n", x, y);
						break;
					case 'C':
						// Start player at location denoted by "C"
						player_start_pos = sf::Vector2f(x, y);
						break;
					case 'X':
						// Start an enemy at locations denoted by "X"
						enemies.push_back(new Mobiles::Enemy(grid_offset, grid_size, sf::Vector2f(x, y),
							gameptr->GetTexture("ENEMY")));
						// Start a coin beneath the enemy
						coins.push_back((new Obstacles::Coin(grid_offset, grid_size, sf::Vector2f(x, y),
							gameptr->GetTexture("COIN"))));
						break;
					case '.':
						coins.push_back((new Obstacles::Coin(grid_offset, grid_size, sf::Vector2f(x, y),
							gameptr->GetTexture("COIN"))));
						break;
					}
					x++; // Increment X and Y to match grid coordinates for sprite placement
				}
				y++;
			}			
		}
		// Close the file
		map_file.close();
	}

	int GameScene::Highscore(bool _write) 
	// Loads the current Hiscore if _write is set to false, else writes a new score to the file
	{
		std::fstream score_file;

		if (!_write) 
		// Load from file
		{			
			score_file.open("Levels/hiscore.txt", std::ios::in);
			if (score_file.is_open()) 
			{
				int hiscore;
				score_file >> hiscore;
				score_file.close();
				return hiscore;
			}
			else 
			{
				// Return -1 as an error value;
				score_file.close();
				return -1;
			}			
		}
		else 
		//Write to file
		{
			score_file.open("Levels/hiscore.txt", std::ios::out);
			if (score_file.is_open()) 
			{
				// Overwrite the current hiscore
				score_file << score;
			}
			score_file.close();

			// Return 0 as a successful write
			return 0;
		}
	}
}