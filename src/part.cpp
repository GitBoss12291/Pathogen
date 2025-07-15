#include "part.hpp"
#include "cell.hpp"
#include "sprite.hpp"
#include "sprite_renderer.hpp"

namespace pathogen
{
	void Part::draw(SpriteRenderer* renderer, float camX, float camY)
	{
		if (!host) return;

		sprite.x = host->baseSprite.x + offsetX;
		sprite.y = host->baseSprite.y + offsetY;

		renderer->drawSprite(sprite, camX, camY);
	}
}