#include "editor.hpp"
#include "cell.hpp"
#include "sprite_renderer.hpp"
#include "input_handler.hpp"

namespace pathogen
{
	void Editor::setTargetCell(Cell* cell)
	{
		currentCell = cell;
	}

	void Editor::tick(float dt)
	{
		cursorPos = InputHandler::getMousePos();
		
	}

	void Editor::draw(SpriteRenderer* renderer, float camX, float camY)
	{
		if (currentCell)
			currentCell->draw(renderer, camX, camY, 0, 0);
	}
}