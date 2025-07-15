#include <GLFW/glfw3.h>

#include "player.hpp"
#include "input_handler.hpp"
#include "sprite_renderer.hpp"

namespace pathogen
{
	void Player::update(float dt)
	{
		if (InputHandler::getKey(GLFW_KEY_W) == GLFW_PRESS)
		{
			sprite.y += cell.stats.speed * dt;
		}

		if (InputHandler::getKey(GLFW_KEY_S) == GLFW_PRESS)
		{
			sprite.y -= cell.stats.speed * dt;
		}

		if (InputHandler::getKey(GLFW_KEY_A) == GLFW_PRESS)
		{
			sprite.x -= cell.stats.speed * dt;
		}

		if (InputHandler::getKey(GLFW_KEY_D) == GLFW_PRESS)
		{
			sprite.x += cell.stats.speed * dt;
		}
	}

	void Player::draw(SpriteRenderer* renderer, float camX, float camY)
	{
		renderer->drawSprite(sprite, camX, camY);
		cell.draw(renderer, camX, camY);
	}
}