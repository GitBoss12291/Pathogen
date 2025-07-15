#include <cmath>

#include "enemy.hpp"
#include "player.hpp"

namespace pathogen
{
	const float MOVE_SPEED = 150.0f;
	const float MIN_DIST = 100.0f;
	const float MAX_DIST = 300.0f;

	void Enemy::update(float dt)
	{
		if (player)
		{
			float directionX = player->x - x;
			float directionY = player->y - y;
			
			float magnitude = std::sqrt(directionX * directionX + directionY * directionY);

			if (magnitude >= MIN_DIST)
			{
				float normDirX = directionX / magnitude;
				float normDirY = directionY / magnitude;

				x += normDirX * MOVE_SPEED * dt;
				y += normDirY * MOVE_SPEED * dt;
			}
		}
	}
}