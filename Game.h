#pragma once

#include <map>
#include <memory>
#include <stack>

#include "SFML/Graphics.hpp"
#include "Scene.h"

namespace Toolbox 
{
	class Scene;

	// Class which controls entirety of game, scene, and asset management
	class Game 
	{
	public:		
		// Asset Management
		std::map<std::string, sf::Texture> textures;
		std::map<std::string, sf::Font> fonts;

		void LoadTexture(std::string _name, std::string _filepath);
		void ResizeSprite(sf::Sprite& _sprite, sf::Vector2u _newsize);
		void LoadFont(std::string _name, std::string _filepath);

		sf::Texture& GetTexture(std::string _name);
		sf::Font& GetFont(std::string _name);

		// Scene Management
		std::stack<Scene*> scenes;

		void PushScene(Scene* _scene);
		void PopScene();
		void SwapScene(Scene* _scene);

		Scene* ActiveScene();

		// Input Management
		bool SpriteClicked(sf::Sprite& _sprite);

		// Program control
		sf::RenderWindow window;

		//Game(int _w, int _h, std::string _title);
		Game();
		~Game();

		void Run();
	};
}