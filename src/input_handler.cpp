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

	float* InputHandler::getMousePos()
	{
		double x;
		double y;

		float pos[2];

		glfwGetCursorPos(window, &x, &y);
		pos[0] = static_cast<float>(x);
		pos[1] = static_cast<float>(y);

		return pos;
	}
}