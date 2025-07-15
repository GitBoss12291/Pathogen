#pragma once

namespace pathogen
{
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
		Part* selectedpart;
		EditMode mode = EditMode::None;
		
		float cursorX = 0.0f;
		float cursorY = 0.0f;
	};
}