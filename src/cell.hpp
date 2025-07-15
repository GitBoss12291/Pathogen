#pragma once

#include <vector>

namespace pathogen
{
	struct Sprite;
	class Part;
	class SpriteRenderer;

	struct CellStats
	{
		float speed = 0.0f;
		float attack = 0.0f;
		float defense = 0.0f;
	};

	class Cell
	{
	public:
		Sprite* sprite;
		std::vector<Part*> parts;

		float x, y;

		CellStats stats;
		float baseSpeed = 200.0f;
		float baseDefense = 0.0f;
		float baseAttack = 0.0f;

		void changeSprite(Sprite& sprite);
		void addPart(Part* part);
		void updateStats();
		void draw(SpriteRenderer* renderer, float camX, float camY, float x, float y);
	};
}