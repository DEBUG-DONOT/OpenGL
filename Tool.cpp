#include"Tool.h"
#include<iostream>
void Initialization::GLFWInitialization()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//���ð汾
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//macosֻ֧��core profile
    glfwWindowHint(GLFW_SAMPLES, 4);

}

int Initialization::GladInitialization()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
}

void Initialization::GlfwWindowJudge(GLFWwindow* window)
{
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        //return -1;
        throw "Failed to create GLFW window";
    }
}

void Initialization::GammaCorrectionControl(bool flag)
{
    if (flag)
    {
        glEnable(GL_FRAMEBUFFER_SRGB);
    }
    else
    {
        glDisable(GL_FRAMEBUFFER_SRGB);
    }
}

GLFWwindow* Initialization::CreateWindow(int width, int high, const char* name)
{
    auto* window= glfwCreateWindow(width, high, name, NULL, NULL);
    return window;
}
