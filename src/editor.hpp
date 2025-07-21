#pragma once

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include <string>

namespace pathogen
{
	class SpriteRenderer;
	class Cell;
	class Part;
	struct Sprite;
	struct UIPanel;
	struct UITextInput;

	enum class EditMode
	{
		None = 0,
		Move,
		Rotate,
		Scale,
		Add,
		Delete
	};

	enum class Direction
	{
		Up = 0,
		Down,
		Left,
		Right
	};

	struct Arrow
	{
		float x, y, rotation;
		Direction direction;
	};

	class Editor
	{
	public:
		Editor(int width, int height);
		void setScreenDim(int height, int width);
		void setTargetCell(Cell* cell);
		void tick(float dt);
		void draw(SpriteRenderer* renderer, float camX, float camY);
		void checkSaves();

		bool exit = false;

	private:
		void drawUI(SpriteRenderer* renderer);
		void drawCellAndArrows(SpriteRenderer* renderer);
		void save();

		int screenHeight, screenWidth;

		Cell* currentCell = nullptr;
		Part* selectedPart = nullptr;
		EditMode mode = EditMode::None;
		std::vector<Part> availableParts = {};

		std::vector<std::string> savedCells;

		Sprite* saveSprite = nullptr;
		glm::vec2 saveButtonPos = {};
		glm::vec4 saveButtonColor = {};

		glm::vec2 exitButtonPos = {};
		
		Sprite* sizeAdjuster = nullptr;
		std::vector<Arrow> arrows;

		glm::vec2 cursorPos = {};
		glm::vec2 prevCursorPos = {};
		glm::vec2 cursorDelta = {};

		UIPanel* saveButton;
		UIPanel* exitButton;

		UITextInput* cellNameInput;
	
		bool isDragging = false;
		Direction dragDirection = Direction::Up;
		float dragAccumulator = 0.0f;
		int dragStartStep = 0;
	};
}