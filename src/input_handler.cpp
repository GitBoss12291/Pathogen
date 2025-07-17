#include <GLFW/glfw3.h>	

#include "input_handler.hpp"

namespace pathogen
{
	GLFWwindow* InputHandler::window = nullptr;

	void InputHandler::init(GLFWwindow* win)
	{
		window = win;
	}

	int InputHandler::getKey(int key)
	{
		return glfwGetKey(window, key);
	}

	int InputHandler::getMouseButton(int button)
	{
		return glfwGetMouseButton(window, button);
	}

	glm::vec2 InputHandler::getMousePos()
	{
		double x;
		double y;

		glfwGetCursorPos(window, &x, &y);
		
		glm::vec2 pos = { x, y };

		return pos;
	}
}