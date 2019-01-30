#include "Mobiles.h"
#include "DEFINITIONS.h"


namespace Mobiles
{
	Player::Player(sf::Vector2f _grid_offset, float _grid_size, 
		sf::Vector2f _start_grid_pos, sf::Texture& _texture)
	{
		// Set up the sprite position and texture
		sprite.setTexture(_texture);
		sprite.setPosition((_start_grid_pos * _grid_size) + _grid_offset);
		start_grid_pos = _start_grid_pos;
		grid_pos = _start_grid_pos;
		grid_offset = _grid_offset;
		grid_size = _grid_size;
		dead = false;
	}

	void Player::Input()
	{
		bool keypress = false;

		// Set delta to direction of keypress, set keypress flag to true
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
		{
			delta_pos = UP;
			keypress = true; 
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
		{ 
			delta_pos = DOWN; 
			keypress = true; 
		}			
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
		{ 
			delta_pos = LEFT;
			keypress = true; 
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
		{ 
			delta_pos = RIGHT;
			keypress = true; 
		}			

		// Only change delta if a keypress has been logged!
		if (keypress) 
		{	
			delta_pos *= speed; 
		}	
	}

	void Player::Update()
	{
		// Store the movement for this tick to be used in right-angle movement checks later
		last_tick_delta = delta_pos;
		// Set the new grid position, and the absolute pixel position
		grid_pos += delta_pos;		
		sf::Vector2i new_pix_pos = sf::Vector2i((grid_pos * grid_size) + grid_offset);
		sprite.setPosition(new_pix_pos.x, new_pix_pos.y);
		//printf("pos: %f, %f\n", sprite.getPosition().x, sprite.getPosition().y);			
	}

	void Player::CheckCollision(std::vector<Obstacles::Wall*>& _obstacles)
	{
		// Move by delta_pos		
		sf::Vector2f old_grid_pos(grid_pos);
		sf::Vector2i new_pix_pos = sf::Vector2i(((old_grid_pos + delta_pos) * grid_size) 
			+ grid_offset);
		sprite.setPosition(new_pix_pos.x, new_pix_pos.y);

		// if collisions occur, undo movement, change delta_pos too
		sf::FloatRect playerbounds = sprite.getGlobalBounds();
		for (uint16_t i = 0; i < _obstacles.size(); i++) 
		{
			sf::FloatRect temp = _obstacles[i]->sprite.getGlobalBounds();
			if (playerbounds.intersects(temp))
			{			
				// if the player is attempting to turn at a right angle, we can keep moving like normal
				if (last_tick_delta.x * delta_pos.x == 0 && last_tick_delta.y * delta_pos.y == 0)
				{ 
					delta_pos = last_tick_delta;
				}
				else 
				{
					delta_pos = ZERO;
				}
				
			}
		}

		// Move player back to old position after checking is done
		sprite.setPosition((old_grid_pos * grid_size) + grid_offset);
	}

	int Player::CoinCollision(std::vector<Obstacles::Coin*>& _coins)
	{
		sf::FloatRect playerbounds = sprite.getGlobalBounds();
		for (uint16_t i = 0; i < _coins.size(); i++)
		{
			sf::FloatRect temp = _coins[i]->sprite.getGlobalBounds();
			if (playerbounds.intersects(temp))
			{
				return i;
			}
		}
		return -1; // Return invalid index to indicate no collision has taken place
	}

	int Player::EnemyCollision(std::vector<Mobiles::Enemy*>& _enemies)
	{
		sf::FloatRect playerbounds = sprite.getGlobalBounds();
		for (uint16_t i = 0; i < _enemies.size(); i++)
		{
			sf::FloatRect temp = _enemies[i]->sprite.getGlobalBounds();
			if (playerbounds.intersects(temp))
			{
				dead = true;
				return i;
			}
		}
		return -1; // Return invalid index to indicate no collision has taken place
	}
}