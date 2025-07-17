#include "editor.hpp"
#include "cell.hpp"
#include "part.hpp"
#include "sprite_renderer.hpp"
#include "input_handler.hpp"
#include "ui_panel.hpp"

namespace pathogen
{
	void Editor::setTargetCell(Cell* cell)
	{
		currentCell = cell;
	}

	void Editor::tick(float dt)
	{
		cursorPos = InputHandler::getMousePos();
		
		if (!currentCell) return;

		
	}

	void Editor::drawUI(SpriteRenderer* renderer)
	{
		UIPanel partsPanel = UIPanel();
		partsPanel.x = 0;
		partsPanel.y = 0;
		partsPanel.width = 280; // TODO: make widht and height dynamic.
		partsPanel.height = 720;
		partsPanel.borderSize = 2.0f;
		partsPanel.fillColor = { 0.3f, 0.3f, 0.3f, 1.0f };
		partsPanel.borderColor = { 0.8f, 0.8f, 0.8f, 1.0f };

		partsPanel.draw(renderer);

		float padding = 2.0f;
		float partSize = 64.0f;

		int columns = static_cast<int>((partsPanel.width - padding) / (partSize + padding));
		if (columns < 1) columns = 1;

		for (size_t i = 0; i < availableParts.size(); ++i)
		{
			int col = i% columns;
			int row = static_cast<int>(i) / columns;

			UIPanel partPanel = UIPanel();
			partPanel.x = partsPanel.x + (col * (partSize + padding));
			partPanel.y = partsPanel.y + (row * (partSize + padding));
			partPanel.width = partSize;
			partPanel.height = partSize;
			partPanel.borderSize = 1.0f;
			partPanel.fillColor = { 0.15f, 0.15f, 0.15f, 1.0f };
			partPanel.borderColor = { 0.5f, 0.5f, 0.5f, 1.0f };

			partPanel.draw(renderer);
		}
	}

	void Editor::draw(SpriteRenderer* renderer, float camX, float camY)
	{
		drawUI(renderer);

		float centerX = 0; // DO NOT CHANGE: for ease of reading
		float centerY = 0; // DO NOT CHANGE: for ease of reading
		if (currentCell)
			currentCell->draw(renderer, camX, camY, centerX, centerY);
	}
}