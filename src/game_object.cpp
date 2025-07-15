#include "game_object.hpp"
#include "sprite_renderer.hpp"

namespace pathogen
{
	void GameObject::draw(SpriteRenderer* renderer, float camX, float camY)
	{
		renderer->drawSprite(sprite, camX, camY);
	}
}