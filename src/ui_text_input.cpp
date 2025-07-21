#include "ui_text_input.hpp"
#include "sprite_renderer.hpp"
#include "input_handler.hpp"

#include <glm/vec2.hpp>
#include <iostream>

namespace pathogen
{
	void UITextInput::draw(SpriteRenderer* renderer) const
	{
		if (borderSize > 1e-6)
		{
			float halfBorder = borderSize * 0.49f;

			renderer->drawRect(x - halfBorder, y - halfBorder, width + borderSize, height + borderSize, borderColor);
		}

		renderer->drawRect(x, y, width, height, fillColor, value, textColor);
	}

	void UITextInput::update(float dt,float screenWidth, float screenHeight)
	{
		float cursorX = InputHandler::getMousePos().x;
		float cursorY = InputHandler::getMousePos().y;

		if (!isActive)
		{
			if (!isMouseOver(cursorX, cursorY, screenWidth, screenHeight)) return;

			if (InputHandler::getMouseDown(0))
			{
				std::cout << "isActive: true" << std::endl;
				isActive = true;
			}
		}

		if (!isMouseOver(cursorX, cursorY, screenWidth, screenHeight) && InputHandler::getMouseDown(0))
		{
			isActive = false;
			return;
		}

		const std::string& inputChars = InputHandler::getInputBuffer();

		for (char c : inputChars)
		{
			if (c >= 32 && c <= 126) value += c;

			std::cout << c;
		}

		InputHandler::clearInputBuffer();

		bool backspace = InputHandler::getKey(KEY_BACKSPACE) == PRESS;

		if (InputHandler::getKeyDown(KEY_ESCAPE))
		{
			isActive = false;
		}

		if (!backspace)
		{
			backspaceHeld = false;
			backspaceHoldTime = 0.0f;
			backspaceRepeatTime = 0.0f;
			return;
		}

		if (!backspaceHeld)
		{
			backspaceHeld = true;
			backspaceHoldTime = 0.0f;
			backspaceRepeatTime = 0.0f;

			if (!value.empty())
				value.pop_back();

			return;
		}

		backspaceHoldTime += dt;

		if (backspaceHoldTime < 0.5f) return;

		backspaceRepeatTime += dt;

		if (backspaceRepeatTime < 0.1f) return;

		backspaceRepeatTime = 0.0f;

		if (!value.empty())
			value.pop_back();
	}
}