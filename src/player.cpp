#include <GLFW/glfw3.h>

#include "player.hpp"
#include "input_handler.hpp"
#include "sprite_renderer.hpp"

namespace pathogen
{
	const float ROT_UP = 0.0f;
	const float ROT_DOWN = 180.0f;
	const float ROT_LEFT = 270.0f;
	const float ROT_RIGHT = 90.0f;

	void Player::update(float dt)
	{
		move(dt);
		
		if (InputHandler::getKey(GLFW_KEY_TAB))
		{
			edit = true;
		}

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
		bool up = InputHandler::getKey(GLFW_KEY_W) == GLFW_PRESS;
		bool down = InputHandler::getKey(GLFW_KEY_S) == GLFW_PRESS;
		bool left = InputHandler::getKey(GLFW_KEY_A) == GLFW_PRESS;
		bool right = InputHandler::getKey(GLFW_KEY_D) == GLFW_PRESS;

		float dx = 0.0f;
		float dy = 0.0f;

		if (up) dy += 1.0f;
		if (down) dy -= 1.0f;
		if (left) dx -= 1.0f;
		if (right) dx += 1.0f;

		if (dx != 0.0f || dy != 0.0f)
		{
			float length = std::sqrt(dx * dx + dy * dy);
			dx /= length;
			dy /= length;

			x += dx * cell.stats.speed * dt;
			y += dy * cell.stats.speed * dt;

			if (std::abs(dx) > std::abs(dy)) // Clamp rotation to four direcitons (up, down, left, right)
			{
				sprite.rotation = dx > 0 ? 90.0f : 270.0f;
			} else
			{
				sprite.rotation = dy > 0 ? 0.0f : 180.0f;
			}
		}
	}
}