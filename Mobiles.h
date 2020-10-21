#pragma once

#include "SFML/Graphics.hpp"
#include "Obstacles.h"
#include "Scene.h"
#include <vector>

namespace Mobiles {
	class Mobile
	// Parent class of all mobile object types -- Players AND enemies
	{
	public:
		//  Defining grid movement in the scene
		float grid_size;
		sf::Vector2f grid_offset;	
		// Defining grid position position of the mob
		sf::Vector2f grid_pos;
		sf::Vector2f delta_pos;
		sf::Vector2f start_grid_pos;
		// Sprite for the mob
		sf::Sprite sprite;

		// Input handles player input (or CPU input for enemies),
		// Update moves the mob, CheckCol'n handles sprite collision detection
		virtual void Update() = 0;
		virtual void CheckCollision(std::vector<Obstacles::Wall*>& _obstacles) = 0;

	};


	class Enemy : public Mobile
	{
		// Class for handling enemies in the game, mostly identical to player apart from Input();
	public:
		Enemy(sf::Vector2f _grid_offset, float _grid_size,
			sf::Vector2f _start_grid_pos, sf::Texture& _texture);
		// AutoInput() takes a "seed" value from the scene its in for random movement
		void AutoInput(int seed);
		void Update();
		void CheckCollision(std::vector<Obstacles::Wall*>& _obstacles);
		sf::Vector2f last_tick_delta;
		float speed = 0.5f;

	private:
		// Modulus for random number generation
		const int RANDMOD = 5;
		int RandomNumber(int seed);
		// Checking if movement last tick was "ZERO", ie. has collided with something
		// This is used to help "unstick" enemies
		bool moving = false;
	};

	class Player : public Mobile
	{
	// Class for handling player movement and other events
	public:
		Player(Toolbox::Scene* _gamescene,  sf::Vector2f _grid_offset, float _grid_size,
			sf::Vector2f _start_grid_pos, sf::Texture& _texture);
		void Input();
		void Update();
		void CheckCollision(std::vector<Obstacles::Wall*>& _obstacles);
		int CoinCollision(std::vector<Obstacles::Coin*>& _coins);
		int EnemyCollision(std::vector<Mobiles::Enemy*>& _enemies);
		// Stores movement from last tick, to stop "sticky" movement along walls
		sf::Vector2f last_tick_delta;
		bool dead = false;
		// Moves 'speed' grid-squares every tick
		float speed = 0.5f; 
		Toolbox::Scene* gamescene;
		
	};


}

