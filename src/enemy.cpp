#include <cmath>
#include <cstdlib>

#include "enemy.hpp"
#include "player.hpp"

namespace pathogen
{
	const float MOVE_SPEED = 150.0f;
	const float MIN_DIST = 100.0f;
	const float MAX_DIST = 300.0f;

	float targetX;
	float targetY;
	float wanderTimer;
	bool hasWanderTarget;

	static float randomF(float min, float max)
	{
		return min + static_cast<float>(std::rand() / (float)RAND_MAX * (max - min));
	}

	void Enemy::update(float dt)
	{
		float directionX = 0;
		float directionY = 0;

		if (player)
		{
			directionX = player->x - x;
			directionY = player->y - y;

			float magnitude = std::sqrt(directionX * directionX + directionY * directionY);
			
			if (magnitude >= MIN_DIST && magnitude <= MAX_DIST)
			{
				float normDirX = directionX / magnitude;
				float normDirY = directionY / magnitude;

				x += normDirX * MOVE_SPEED * dt;
				y += normDirY * MOVE_SPEED * dt;
				
				if (hasWanderTarget)
					hasWanderTarget = false;
				return;
			}
		}

		if (!hasWanderTarget)
		{
			float radius = 200.0f;
			targetX = x + randomF(-radius, radius);
			targetY = y + randomF(-radius, radius);
			hasWanderTarget = true;
		}

		directionX = targetX - x;
		directionY = targetY - y;
		float dist = std::sqrt(directionX * directionX + directionY * directionY);

		if (dist > 5.0f)
		{
			float normDirX = directionX / dist;
			float normDirY = directionY / dist;
			x += normDirX * MOVE_SPEED * 0.5f * dt; // Slower wander speed;
			y += normDirY * MOVE_SPEED * 0.5f * dt;
		}
		else
		{
			wanderTimer += dt;
			if (wanderTimer >= 0.5f)
			{
				wanderTimer = 0.0f;
				hasWanderTarget = false;
			}
		}
	}
}