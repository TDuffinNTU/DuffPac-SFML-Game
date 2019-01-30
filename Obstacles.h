#pragma once

#include "SFML/Graphics.hpp"

namespace Obstacles 
{
	class Wall 
	{
	public:
		sf::Vector2f grid_offset;
		float grid_size;
		sf::Vector2f grid_pos;
		sf::Vector2f delta_pos;
		sf::Sprite sprite;

		Wall(sf::Vector2f _grid_offset, float _grid_size, 
			sf::Vector2f _start_grid_pos, sf::Texture& _texture);
	};

	class Coin 
	{
	public:
		sf::Vector2f grid_offset;
		float grid_size;
		sf::Vector2f grid_pos;
		sf::Vector2f delta_pos;
		sf::Sprite sprite;

		Coin(sf::Vector2f _grid_offset, float _grid_size,
			sf::Vector2f _start_grid_pos, sf::Texture& _texture);

		const int score = 50;
	};

}


