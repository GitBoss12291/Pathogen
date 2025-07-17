#pragma once

#include <glm/vec2.hpp>

struct GLFWwindow;

namespace pathogen
{
	static class InputHandler
	{
	public:
		static void init(GLFWwindow* win);
		
		static int getKey(int key);
		static int getMouseButton(int button);

		static glm::vec2 getMousePos();

	private:
		static GLFWwindow* window;
	};
}