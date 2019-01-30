#include "Mobiles.h"
#include "DEFINITIONS.h"

namespace Mobiles
{
	Enemy::Enemy(sf::Vector2f _grid_offset, float _grid_size,
		sf::Vector2f _start_grid_pos, sf::Texture& _texture)
	{
		// Set up the sprite position and texture
		sprite.setTexture(_texture);
		sprite.setPosition((_start_grid_pos * _grid_size) + _grid_offset);
		start_grid_pos = _start_grid_pos;
		grid_pos = _start_grid_pos;
		grid_offset = _grid_offset;
		grid_size = _grid_size;
	}

	void Enemy::AutoInput(int seed)
	// Unlike the Player class, we choose the direction based on a random number
	{	
		// Only check if gridpos is an int val
		if (std::ceilf(grid_pos.x) == grid_pos.x && std::ceilf(grid_pos.y) == grid_pos.y) {
			// flag to check if the delta_pos value has been reset
			bool delta_changed = true;

			// Set direction using random number generator
			switch (RandomNumber(seed))
			{
			case 0:
				delta_pos = UP;
				break;
			case 1:
				delta_pos = DOWN;
				break;
			case 2:
				delta_pos = LEFT;
				break;
			case 3:
				delta_pos = RIGHT;
				break;
			default:
				delta_changed = false;
				break;
			}

			// Stop the ghosts moving back and forth in same position
			if (!moving || (delta_pos.x *-1.f == last_tick_delta.x && delta_pos.y*-1.f == last_tick_delta.y))
			{
				delta_pos *= -1.f;
			}

			// if delta_pos has been reset, multiply it with speed
			if (delta_changed)
			{
				delta_pos *= speed;
			}
		}
	}

	void Enemy::Update()
	{
		// Store the movement for this tick to be used in right-angle movement checks later
		last_tick_delta = delta_pos;

		moving = true;
		if (delta_pos == ZERO) 
		{
			moving = false;
		}
		
		// Set the new grid position, and the absolute pixel position
		grid_pos += delta_pos;
		sf::Vector2i new_pix_pos = sf::Vector2i((grid_pos * grid_size) + grid_offset);
		sprite.setPosition(new_pix_pos.x, new_pix_pos.y);
		//printf("pos: %f, %f\n", sprite.getPosition().x, sprite.getPosition().y);			
	}

	void Enemy::CheckCollision(std::vector<Obstacles::Wall*>& _obstacles)
	// Collision detection
	{
		// Move by delta_pos to "proposed" new position	
		sf::Vector2f old_grid_pos(grid_pos);
		sf::Vector2i new_pix_pos = sf::Vector2i(((old_grid_pos + delta_pos) * grid_size)
			+ grid_offset);
		sprite.setPosition(new_pix_pos.x, new_pix_pos.y);

		// if collisions occur, undo movement, validate delta_pos to acceptable value
		sf::IntRect playerbounds = sf::IntRect(sprite.getGlobalBounds());
		for (uint16_t i = 0; i < _obstacles.size(); i++)
		{
			sf::IntRect temp = sf::IntRect(_obstacles[i]->sprite.getGlobalBounds());
			if (playerbounds.intersects(temp))
			{
				// if the enemy is attempting to turn at a right angle, we can keep moving like normal
				if (last_tick_delta.x * delta_pos.x == 0 && last_tick_delta.y * delta_pos.y == 0)
				{
					delta_pos = last_tick_delta;
				}
				else
				{
					//Rather than setting to zero, how about rotate delta, try again until it works?
					//delta_pos = sf::Vector2f(delta_pos.y * -1.f, delta_pos.x);
					//CheckCollision(_obstacles);
					delta_pos = ZERO;
				}

				// Return once ANY collision has been detected, instead of wasting time checking for others
				//return;
			}
		}
		// Move player back to old position after checking is done
		sprite.setPosition((old_grid_pos * grid_size) + grid_offset);
	}

	int Enemy::RandomNumber(int seed)
	// Returns a random number for movement
	{
		std::srand(seed);
		int num = std::rand() % RANDMOD;
		//printf("%i\n", num);
		return num;
		
	}
}