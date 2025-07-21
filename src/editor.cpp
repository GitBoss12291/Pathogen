#include "editor.hpp"
#include "cell.hpp"
#include "part.hpp"
#include "sprite_renderer.hpp"
#include "input_handler.hpp"
#include "ui_panel.hpp"
#include "ui_text_input.hpp"
#include "sprite.hpp"
#include "serializer.hpp"

#include <iostream>
#include <filesystem>
#include <GLFW/glfw3.h>

namespace pathogen
{
	static std::string remove_extension(const std::string& path) {
		if (path == "." || path == "..")
			return path;

		size_t pos = path.find_last_of("\\/.");
		if (pos != std::string::npos && path[pos] == '.')
			return path.substr(0, pos);

		return path;
	}

	Editor::Editor(int width, int height)
	{
		screenWidth = width;
		screenHeight = height;
		sizeAdjuster = new Sprite();
		sizeAdjuster->texPath = "arrow-up.png";
		sizeAdjuster->width = 100.0f;
		sizeAdjuster->height = 100.0f;
		sizeAdjuster->scale = 0.5f;
		sizeAdjuster->step = 0;
		sizeAdjuster->maxSteps = 2;
		sizeAdjuster->cols = 2;
		sizeAdjuster->rows = 1;

		saveSprite = new Sprite();
		saveSprite->texPath = "save.png";
		saveSprite->width = 100.0f;
		saveSprite->height = 50.0f;
		saveSprite->scale = 2.0f;
		saveSprite->step = 0;
		saveSprite->maxSteps = 1;
		saveSprite->cols = 1;
		saveSprite->rows = 1;

		saveButton = new UIPanel();
		exitButton = new UIPanel();
		cellNameInput = new UITextInput();
	}

	void Editor::setScreenDim(int width, int height)
	{
		screenHeight = height;
		screenWidth = width;
	}

	void Editor::setTargetCell(Cell* cell)
	{
		currentCell = cell;
	}

	void Editor::tick(float dt)
	{
		cellNameInput->update(dt, screenWidth, screenHeight);

		cursorPos = InputHandler::getMousePos();

		cursorDelta = cursorPos - prevCursorPos;
		prevCursorPos = cursorPos;

		if (!currentCell) return;

		bool mouseDown = (InputHandler::getMouseButton(0) == GLFW_PRESS);

		if (!mouseDown)
		{
			isDragging = false;
			return;
		}

		if (exitButton->isMouseOver(cursorPos.x, cursorPos.y, screenWidth, screenHeight))
		{
			exit = true;
		}

		if (saveButton->isMouseOver(cursorPos.x, cursorPos.y, screenWidth, screenHeight))
		{
			save();
		}

		if (!isDragging)
		{
			for (const Arrow& arrow : arrows)
			{
				float halfW = sizeAdjuster->width * sizeAdjuster->scale * 0.5f;
				float halfH = sizeAdjuster->height * sizeAdjuster->scale * 0.5f;

				float mouseX = cursorPos.x;
				float mouseY = cursorPos.y;

				glm::vec2 screenPos =
				{
					arrow.x + (screenWidth * 0.5f),
					(screenHeight * 0.5f) - arrow.y
				};

				float sizeX = sizeAdjuster->width * sizeAdjuster->scale;
				float sizeY = sizeAdjuster->height * sizeAdjuster->scale;

				int step;

				if (mouseX >= screenPos.x - (sizeX * 0.5f) &&
					mouseX <= screenPos.x + (sizeX * 0.5f) &&
					mouseY >= screenPos.y - (sizeY * 0.5f) &&
					mouseY <= screenPos.y + (sizeY * 0.5f))
				{

					isDragging = true;
					dragDirection = arrow.direction;
					dragAccumulator = 0.0f;
					dragStartStep = (arrow.direction == Direction::Up || arrow.direction == Direction::Down) ? 14 : 0;

					break;
				}
			}
			
			return;
		}
		int baseStep = 0;
		int stepRange = 13; // 0-13 and 14-27
		float stepChange = 0.0f;

		switch (dragDirection)
		{
		case Direction::Up:
			baseStep = 14;
			dragAccumulator += cursorDelta.y;
			stepChange = dragAccumulator / 5.0f;
			break;
		case Direction::Down:
			baseStep = 14;
			dragAccumulator += cursorDelta.y;
			stepChange = -dragAccumulator / 5.0f;
			break;
		case Direction::Left:
			baseStep = 0;
			dragAccumulator += cursorDelta.x;
			stepChange = dragAccumulator / 5.0f;
			break;
		case Direction::Right:
			baseStep = 0;
			dragAccumulator += cursorDelta.x;
			stepChange = -dragAccumulator / 5.0f;
			break;
		}

		int newStep = dragStartStep + static_cast<int>(stepChange);

		if (newStep < baseStep) newStep = baseStep;
		if (newStep > baseStep + stepRange) newStep = baseStep + stepRange;

		currentCell->sprite->step = newStep;
	}

	void Editor::drawUI(SpriteRenderer* renderer)
	{
		UIPanel partsPanel = UIPanel();
		partsPanel.x = 0;
		partsPanel.y = 0;
		partsPanel.width = screenWidth / 4.0f;
		partsPanel.height = screenHeight;
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

		saveButton->width = 97.0f;
		saveButton->height = 47.0f;
		saveButton->x = screenWidth - (saveButton->width + 5.0f);
		saveButton->y = screenHeight - (saveButton->height + 5.0f);
		saveButton->borderSize = 3.0f;
		saveButton->fillColor = { 0.3f, 0.3f, 0.6f, 1.0f };
		saveButton->borderColor = { 0.2f, 0.2f, 0.5f, 1.0f };

		saveButtonPos = { saveButton->x / screenWidth, saveButton->y / screenHeight };
		saveButtonColor = saveButton->fillColor;

		saveButton->draw(renderer);

		exitButton->width = 97.0f;
		exitButton->height = 47.0f;
		exitButton->x = screenWidth - (saveButton->width + 2 * exitButton->width + 10.0f);
		exitButton->y = screenHeight - (saveButton->height + 5.0f);
		exitButton->borderSize = 3.0f;
		exitButton->fillColor = { 0.3f, 0.3f, 0.6f, 1.0f };
		exitButton->borderColor = { 0.2f, 0.2f, 0.5f, 1.0f };

		exitButtonPos = { exitButton->x / screenWidth, exitButton->y / screenHeight };

		exitButton->draw(renderer);

		cellNameInput->width = 200.0f;
		cellNameInput->height = 100.0f;
		cellNameInput->x = (screenWidth * 0.5f) + (cellNameInput->width * 0.5);
		cellNameInput->y = 5.0f;
		cellNameInput->borderSize = 3.0f;

		cellNameInput->fillColor = { 0.3f, 0.3f, 0.6f, 1.0f };
		cellNameInput->borderColor = { 0.2f, 0.2f, 0.5f, 1.0f };
		
		cellNameInput->draw(renderer);
	}

	void Editor::drawCellAndArrows(SpriteRenderer* renderer)
	{
		float centerX = 150.0f; // DO NOT CHANGE: for ease of reading
		float centerY = 0; // DO NOT CHANGE: for ease of reading
		if (currentCell)
		{
			currentCell->draw(renderer, 0, 0, centerX, centerY);

			float offsetX = currentCell->sprite->width + 20.0f; // additional padding so not touching cell
			float offsetY = currentCell->sprite->height + 20.0f;

			arrows =
			{
				{centerX, centerY + offsetY, 0.0f, Direction::Up},
				{centerX + offsetX, centerY, -90.0f, Direction::Right},
				{centerX, centerY - offsetY, 180.0f, Direction::Down},
				{centerX - offsetX, centerY, 90.0f, Direction::Left}
			};

			for (const Arrow& arrow : arrows)
			{
				sizeAdjuster->rotation = arrow.rotation;
				renderer->drawSprite(*sizeAdjuster, arrow.x, arrow.y, 0, 0, sizeAdjuster->color,
					sizeAdjuster->maxSteps, sizeAdjuster->cols, sizeAdjuster->rows);
			}
		}
	}

	void Editor::draw(SpriteRenderer* renderer, float camX, float camY)
	{
		drawCellAndArrows(renderer);
	
		drawUI(renderer);
	}

	void Editor::checkSaves()
	{
		savedCells.clear();
		for (const auto& entry : std::filesystem::directory_iterator("save"))
		{
			if (entry.path().extension() == ".cell")
			{
				savedCells.push_back(remove_extension(entry.path().filename().string()));
			}
		}
	}

	void Editor::save()
	{
		std::cout << "INFO: SAVING" << std::endl;
		Serializer::save(currentCell, "saveTest.cell");
	}
}