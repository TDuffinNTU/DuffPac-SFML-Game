#include "Entity.h"



Entity::Entity(Grid* _grid, Cell* _initial_cell, sf::Texture& _texture)
{
	grid = _grid;
	current_cell = _initial_cell;
	sprite.setTexture = _texture;
	position = sf::Vector2f(current_cell->pixel_x, 
							current_cell->pixel_y);

}



