#pragma once

#include <glm/vec4.hpp>

namespace pathogen
{
	struct Sprite;
	class SpriteRenderer;

	struct UIPanel
	{
		float x, y, width, height, borderSize;
		glm::vec4 borderColor;
		glm::vec4 fillColor;

		void draw(SpriteRenderer* renderer) const;
	};
}