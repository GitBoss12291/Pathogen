#pragma once

#include <glm/vec2.hpp>
#include <vector>

namespace pathogen
{
	class SpriteRenderer;
	class Cell;
	class Part;

	enum class EditMode
	{
		None = 0,
		Move,
		Rotate,
		Scale,
		Add,
		Delete
	};

	class Editor
	{
	public:
		void setTargetCell(Cell* cell);
		void tick(float dt);
		void draw(SpriteRenderer* renderer, float camX, float camY);

	private:
		void drawUI(SpriteRenderer* renderer);

		Cell* currentCell = nullptr;
		Part* selectedPart = nullptr;
		EditMode mode = EditMode::None;
		std::vector<Part> availableParts = {};
		
		glm::vec2 cursorPos = {};
	};
}