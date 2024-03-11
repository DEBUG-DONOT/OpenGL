#include <iostream>
#include<glad/glad.h>//gald放在glfw前面
#include<GLFW/glfw3.h>
#include"Tool.h"
int main()
{
    Initialization::GLFWInitialization();
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    Initialization::GlfwWindowJudge(window);
    glfwMakeContextCurrent(window);
    Initialization::GladInitialization();
    glViewport(0, 0, 800, 600);
    //渲染循环
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}


