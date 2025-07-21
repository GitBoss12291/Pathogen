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

		virtual void draw(SpriteRenderer* renderer) const;
		bool isMouseOver(float mouseX, float mouseY, float screenWidth, float screenHeight) const;
	};
}