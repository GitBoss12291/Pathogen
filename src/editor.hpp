#pragma once

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
		Cell* currentCell;
		Part* selectedPart;
		EditMode mode = EditMode::None;
		
		float* cursorPos;
	};
}