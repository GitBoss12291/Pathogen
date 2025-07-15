#pragma once

struct GLFWwindow;

namespace pathogen
{
	static class InputHandler
	{
	public:
		static void init(GLFWwindow* win);
		
		static int getKey(int key);

	private:
		static GLFWwindow* window;
	};
}