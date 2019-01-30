#pragma once

#include "SFML/Graphics.hpp"
#include "Grid.h"
#include <stack>


/* The Entity class combines both moving and static objects that populate the game
   level (grid) */
class Entity
{
protected:
	int ID;
	
	sf::Sprite sprite;
	sf::Vector2f position;
	
	Grid* grid;
	Cell* current_cell;

public:	
	Entity(Grid* _grid, Cell* _initial_cell, sf::Texture& _texture);	
};


class MobState 
{
public:
};


class Mobile : Entity
{
public:
	std::stack<MobState*> mob_states;

	
};
