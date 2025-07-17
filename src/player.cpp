#include <GLFW/glfw3.h>

#include "player.hpp"
#include "input_handler.hpp"
#include "sprite_renderer.hpp"

namespace pathogen
{
	void Player::update(float dt)
	{
		move(dt);
	
	}

	void Player::draw(SpriteRenderer* renderer, float camX, float camY)
	{
		cell.x = x;
		cell.y = y;
		if (!cell.sprite) cell.sprite = &sprite;
		cell.draw(renderer, camX, camY, x, y);
	}

	void Player::move(float dt)
	{
		if (InputHandler::getKey(GLFW_KEY_W) == GLFW_PRESS)
		{
			y += cell.stats.speed * dt;
		}

		if (InputHandler::getKey(GLFW_KEY_S) == GLFW_PRESS)
		{
			y -= cell.stats.speed * dt;
		}

		if (InputHandler::getKey(GLFW_KEY_A) == GLFW_PRESS)
		{
			x -= cell.stats.speed * dt;
		}

		if (InputHandler::getKey(GLFW_KEY_D) == GLFW_PRESS)
		{
			x += cell.stats.speed * dt;
		}
	}
}