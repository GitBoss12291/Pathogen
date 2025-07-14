#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>

const float CLEAR_R = 0.1f;
const float CLEAR_G = 0.075f;
const float CLEAR_B = 0.125f;
const float CLEAR_A = 1.0f;

void resizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    
    glClearColor(CLEAR_R, CLEAR_G, CLEAR_B, CLEAR_A);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glfwSwapBuffers(window);
}

int main()
{
    if (!glfwInit())
    {
        std::cout << "GLFW failed to initialize" << std::endl;
        return 0;
    }

    GLFWwindow* window = glfwCreateWindow(960, 720, "Pathogen", NULL, NULL);

    if (window == NULL) 
    {
        std::cout << "GLFW failed to create a window" << std::endl;
        return 0;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetWindowSizeCallback(window, resizeCallback);

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(CLEAR_R, CLEAR_G, CLEAR_B, CLEAR_A);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}