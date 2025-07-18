#include "part.hpp"
#include "cell.hpp"
#include "sprite.hpp"
#include "sprite_renderer.hpp"

namespace pathogen
{
	void Part::draw(SpriteRenderer* renderer, float camX, float camY, glm::vec4 color)
	{
		if (!host) return;

		float x = host->x + offsetX;
		float y = host->y + offsetY;

		renderer->drawSprite(sprite, x, y, camX, camY, color);
	}
}