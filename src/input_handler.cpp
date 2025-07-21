#include <GLFW/glfw3.h>	

#include "input_handler.hpp"

namespace pathogen
{
	GLFWwindow* InputHandler::window = nullptr;

	std::unordered_map<int, int> InputHandler::keyState;
	std::unordered_map<int, int> InputHandler::prevKeyState;

	std::unordered_map<int, int> InputHandler::mouseState;
	std::unordered_map<int, int> InputHandler::prevMouseState;

	std::string InputHandler::inputBuffer;

	void InputHandler::charCallback(GLFWwindow* window, unsigned int codepoint)
	{
		inputBuffer += static_cast<char>(codepoint);
	}

	void InputHandler::init(GLFWwindow* win)
	{
		window = win;
		glfwSetCharCallback(window, charCallback);
	}

	void InputHandler::update()
	{
		prevKeyState = keyState;
		prevMouseState = mouseState;

		for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key)
			keyState[key] = glfwGetKey(window, key);

		for (int btn = GLFW_MOUSE_BUTTON_1; btn <= GLFW_MOUSE_BUTTON_LAST; ++btn)
			mouseState[btn] = glfwGetMouseButton(window, btn);
	}

	int InputHandler::getKey(int key)
	{
		return glfwGetKey(window, key);
	}

	bool InputHandler::getKeyDown(int key)
	{
		return keyState[key] == GLFW_PRESS && prevKeyState[key] == GLFW_RELEASE;
	}

	bool InputHandler::getKeyUp(int key)
	{
		return keyState[key] == GLFW_RELEASE && prevKeyState[key] == GLFW_PRESS;
	}

	int InputHandler::getMouseButton(int button)
	{
		return glfwGetMouseButton(window, button);
	}

	bool InputHandler::getMouseDown(int button)
	{
		return mouseState[button] == GLFW_PRESS && prevMouseState[button] == GLFW_RELEASE;
	}

	bool InputHandler::getMouseUp(int button)
	{
		return mouseState[button] == GLFW_RELEASE && prevMouseState[button] == GLFW_PRESS;
	}

	glm::vec2 InputHandler::getMousePos()
	{
		double x;
		double y;

		glfwGetCursorPos(window, &x, &y);
		
		glm::vec2 pos = { x, y };

		return pos;
	}

	const std::string& InputHandler::getInputBuffer()
	{
		return inputBuffer;
	}

	void InputHandler::clearInputBuffer()
	{
		inputBuffer.clear();
	}
}