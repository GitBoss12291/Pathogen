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
}