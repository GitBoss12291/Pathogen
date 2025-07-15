#pragma once

namespace pathogen
{
	enum class PartType { Flagella, Spike, Shell };
	
	struct Sprite;
	class Cell;
	class SpriteRenderer;

	class Part
	{
	public:
		Cell* host;
		PartType type;
		Sprite sprite;
		float offsetX, offsetY;
		virtual void modifyStats() = 0;
		virtual void draw(SpriteRenderer* renderer, float camX, float camY);
		virtual ~Part() = default;
	};
}