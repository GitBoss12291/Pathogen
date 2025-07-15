#include "cell.hpp"
#include "part.hpp"
#include "sprite.hpp"
#include "sprite_renderer.hpp"

namespace pathogen
{
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

	void Cell::draw(SpriteRenderer* renderer, float camX, float camY)
	{
		renderer->drawSprite(baseSprite, camX, camY);

		for (auto& part : parts)
		{
			part->draw(renderer, camX, camY);
		}
	}
}