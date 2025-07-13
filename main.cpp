#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main()
{
    if (!glfwInit())
    {
        std::cout << "GLFW failed to initialize" << std::endl;
        return 0;
    }

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Pathogen", NULL, NULL);

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

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.075f, 0.125f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}