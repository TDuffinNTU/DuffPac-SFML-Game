#include "Game.h"
#include "DEFINITIONS.h"

// Toolbox -- The namespace for Simple_Toolbox
namespace Toolbox 
{
	// Game class constructor
	Game::Game() {
		window.create(sf::VideoMode(WIDTH, HEIGHT), TITLE, sf::Style::Close);
		window.setFramerateLimit(FRAMERATE);
	}

	// FOLLOWING CODE SOURCED FROM (OR HEAVILY INFLUENCED BY):
	// https://www.binpress.com/tutorial/creating-a-city-building-game-with-sfml-part-1-state-manager/123

	// Deconstructor
	Game::~Game() 
	{
		// Remove all scenes from the stack
		while (!scenes.empty())
		{
			scenes.pop();
		}
	}

	// Pushes a scene to the top of the stack, which will make it the active state
	void Game::PushScene(Scene* _scene) 
	{
		scenes.push(_scene);
	}

	// Removes a scene from the stack, deletes it from memory
	void Game::PopScene()
	{
		delete scenes.top();
		scenes.pop();
	}

	// Pops the active scene from the stack, replaces it with another scene
	void Game::SwapScene(Scene* _scene)
	{
		if (!scenes.empty()) scenes.pop();
		scenes.push(_scene);
	}

	// Returns the currently active scene for execution
	Scene* Game::ActiveScene() 
	{
		// Return nullptr if there are no scenes in the stack
		if (scenes.empty()) 
			return nullptr;
		// Top scene of the stack is the active scene
		return scenes.top();
	}

	// END OF CODE SOURCED FROM (OR HEAVILY INFLUENCED BY):
	// https://www.binpress.com/tutorial/creating-a-city-building-game-with-sfml-part-1-state-manager/123

	// FOLLOWING CODE SOURCED FROM (OR HEAVILY INFLUENCED BY):
	// https://www.youtube.com/watch?v=tgXEws1Ef8s

	// Asset loaders, which ensure that assets are only loaded once from disk
	void Game::LoadTexture(std::string _name, std::string _filepath) 
	{
		sf::Texture temp;
		if (temp.loadFromFile(_filepath))
			textures[_name] = temp;
		else
			printf("Failed to load Texture '%s' from location '%s'.\n", _name, _filepath);
	}

	void Game::LoadFont(std::string _name, std::string _filepath)
	{
		sf::Font temp;
		if (temp.loadFromFile(_filepath))
			fonts[_name] = temp;
		else
			printf("Failed to load Font '%s' from location '%s'.\n", _name, _filepath);
	}

	// ENF OF CODE SOURCED FROM (OR HEAVILY INFLUENCED BY):
	// https://www.youtube.com/watch?v=tgXEws1Ef8s

	// Asset "Getters" That return references to previously saved assets
	sf::Texture& Game::GetTexture(std::string _name) 
	{
		return textures[_name];
	}

	sf::Font& Game::GetFont(std::string _name)
	{
		return fonts[_name];
	}

	//Checking whether a sprite has been clicked by the user
	bool  Game::SpriteClicked(sf::Sprite& _sprite)
	{
		return _sprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)));
	}	

	// Runs the program until it's closed
	void Game::Run() 
	{
		sf::Clock clock;

		while (window.isOpen()) 
		{
			// FOLLOWING CODE SOURCED FROM (OR HEAVILY INFLUENCED BY):
			// https://www.binpress.com/tutorial/creating-a-city-building-game-with-sfml-part-1-state-manager/123

			// set the frametime for each frame
			sf::Time frame_time = clock.restart();
			float dt = frame_time.asSeconds();

			if (ActiveScene() == nullptr) continue;

			// END OF CODE SOURCED FROM (OR HEAVILY INFLUENCED BY):
			// https://www.binpress.com/tutorial/creating-a-city-building-game-with-sfml-part-1-state-manager/123

			// Execute the current Scene
			ActiveScene()->Input(); 
			ActiveScene()->Update(dt); 

			// Draw the current scene
			window.clear(sf::Color::Magenta);
			ActiveScene()->Draw(dt);
			window.display();
		}
	}



}