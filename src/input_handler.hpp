#pragma once

#include "input_codes.hpp"

#include <glm/vec2.hpp>
#include <string>
#include <unordered_map>

struct GLFWwindow;

namespace pathogen
{
	static class InputHandler
	{
	public:
		static void init(GLFWwindow* win);

		static void update();
		
		static int getKey(int key);
		static bool getKeyDown(int key);
		static bool getKeyUp(int key);

		static int getMouseButton(int button);
		static bool getMouseDown(int button);
		static bool getMouseUp(int button);

		static glm::vec2 getMousePos();

		static const std::string& getInputBuffer();
		static void clearInputBuffer();

	private:
		static GLFWwindow* window;

		static std::unordered_map<int, int> keyState;
		static std::unordered_map<int, int> prevKeyState;

		static std::unordered_map<int, int> mouseState;
		static std::unordered_map<int, int> prevMouseState;

		static std::string inputBuffer;

		static void charCallback(GLFWwindow* win, unsigned int codepoint);
	};
}