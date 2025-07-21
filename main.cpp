#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "game.hpp"
#include "input_handler.hpp"

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 720;

using namespace pathogen;

static void resizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

static GLFWwindow* initGLFWAndWindow()
{
	if (!glfwInit())
	{
		std::cerr << "GLFW failed to initialize\n";
		return nullptr;
	}

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pathogen", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, resizeCallback);
	return window;
}

static bool initOpenGL()
{
	if (!gladLoadGL(glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD\n";
		return false;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return true;
}

static void initGame(Game& game)
{
	game.init(SCREEN_WIDTH, SCREEN_HEIGHT);
}

int main()
{
	GLFWwindow* window = initGLFWAndWindow();
	if (!window) return -1;

	if (!initOpenGL()) return -1;

	InputHandler::init(window);

	Game game;
	initGame(game);

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.2f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		game.setScreenDim(width, height);

		game.tick(deltaTime);
		game.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
