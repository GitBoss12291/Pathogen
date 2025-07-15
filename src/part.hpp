#pragma once

namespace pathogen
{
	enum class PartType { Flagella, Spike, Shell };

	class Cell;
	class SpriteRenderer;

	class Part
	{
	public:
		PartType type;
		Sprite sprite;
		float offsetX, offsetY;
		virtual void modifyStats(Cell& host) = 0;
		virtual void draw(SpriteRenderer* renderer, float camX, float camY);
		virtual ~Part() = default;
	};
}