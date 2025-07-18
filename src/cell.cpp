#include "cell.hpp"
#include "part.hpp"
#include "sprite.hpp"
#include "sprite_renderer.hpp"

namespace pathogen
{
	void Cell::changeSprite(Sprite& sprite)
	{
		this->sprite = &sprite;
	}

	void Cell::addPart(Part* part)
	{
		part->host = this;
		parts.push_back(part);
		updateStats();
	}

	void Cell::updateStats()
	{
		stats = { baseSpeed, baseAttack, baseDefense };

		for (auto& part : parts)
		{
			part->modifyStats();
		}
	}

	void Cell::draw(SpriteRenderer* renderer, float camX, float camY, float x, float y)
	{
		renderer->drawSprite(*sprite, x, y, camX, camY, sprite->color, sprite->maxSteps, sprite->cols, sprite->rows);

		for (auto& part : parts)
		{
			part->draw(renderer, camX, camY, partColor);
		}
	}
}