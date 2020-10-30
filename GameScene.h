#pragma once

#include "Scene.h"
#include "Mobiles.h"
#include "Obstacles.h"

#include <map>
#include <memory>
#include <stack>


namespace Toolbox 
{
	class GameScene : public Scene
	{
	public:
		void Input();
		void Tick();
		void Update(const float dt);
		void Draw(const float dt);		

		GameScene(Game* game);
	private:
		// Refactor: Implementing an FSM to make gameflow much easier to understand
		sf::Color ghost_cols[5] = {sf::Color(200,50,50), sf::Color(80,80,255), sf::Color::Yellow, sf::Color(0,200,0), sf::Color(255,165,0)};


		// Main scene clock, initial countdown variables
		sf::Clock clock;
		const float READYTIME = 3.0f;
		const float TICK = 0.10f;	
		int countdown;
		bool started = false;

		// Game over clock and display
		sf::Clock game_over_clock;
		const float GAMEOVERBLINK = 0.5f;
		bool blink = false;
		const float GAMEOVERDISPLAY = 3.0f;		

		// text objects for the scene
		sf::Text txt_header;		
		sf::Text txt_score;
		sf::Text txt_hi_score;

		// Score, Hiscore
		int score = 0;
		int hi_score;
		bool new_hi_score = false;
		const float TIMESCORETICK = 0.05f;
		const int SCORETICK = 2;

		// Background image and buttons
		sf::Sprite btn_return;
		sf::Sprite btn_restart;
		sf::Sprite bg;

		// Grid definition variables
		sf::Vector2f grid_offset;
		float grid_size;

		// Player class instance
		Mobiles::Player* player;
		sf::Vector2f player_start_pos;

		// Wall instances
		Obstacles::Wall* wall;
		std::vector<Obstacles::Wall*> walls;

		// Enemy instances and clock for random seeding
		sf::Clock rand_clock;
		Mobiles::Enemy* enemy;
		std::vector<Mobiles::Enemy*> enemies;
		std::vector<sf::Vector2f> enemy_start_pos;
		bool show_end_buttons = false;

		// Coin instances
		Obstacles::Coin* coin;
		std::vector<Obstacles::Coin*> coins;

		// Extra methods
		void CheckClicked();
		void LoadLevel();	
		int Highscore(bool _write);
	};
}