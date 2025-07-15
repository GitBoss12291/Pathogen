#pragma once

namespace pathogen
{
	struct Sprite;
	class SpriteRenderer;

	struct UIPanel
	{
		float x, y, width, height;
		float* borderColor;
		float* fillColor;

		void draw(SpriteRenderer* renderer);
	};
}