#include "Obstacles.h"

namespace Obstacles 
{
	// Similar constructor class to both the 
	Coin::Coin(sf::Vector2f _grid_offset, float _grid_size, sf::Vector2f _start_grid_pos,
		sf::Texture& _texture)
	{
		sprite.setTexture(_texture);
		sprite.setPosition((_start_grid_pos * _grid_size) + _grid_offset);
		grid_offset = _grid_offset;
		grid_size = _grid_size;
	}
}