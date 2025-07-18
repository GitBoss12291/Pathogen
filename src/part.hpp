#pragma once

#include "sprite.hpp"

namespace pathogen
{
	enum class PartType { Flagella, Spike, Shell };

	class Cell;
	class SpriteRenderer;

	class Part
	{
	public:
		int instanceID = -1;

		Cell* host;
		PartType type;
		Sprite sprite;
		float offsetX, offsetY;
		virtual void modifyStats() = 0;
		virtual void draw(SpriteRenderer* renderer, float camX, float camY, glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f});
		virtual ~Part() = default;
	};
}