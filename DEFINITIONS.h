#pragma once
#include "SFML\Graphics.hpp"

// Vector directions
const sf::Vector2f UP	(0, -1);
const sf::Vector2f DOWN	(0, 1);
const sf::Vector2f LEFT	(-1, 0);
const sf::Vector2f RIGHT(1, 0);
const sf::Vector2f ZERO	(0, 0);

// sprite rotations
const float ROT_UP = 270;
const float ROT_DOWN = 90; 
const float ROT_LEFT = 180;
const float ROT_RIGHT = 0;

// Window attributes
const std::string TITLE = "DuffPac -- Simple_Toolbox";
const int WIDTH = 1280;
const int HEIGHT = 720;
const int FRAMERATE = 60;

