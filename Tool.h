#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
class Initialization
{
public:
	static void GLFWInitialization();
	static int GladInitialization();
	static void OpenGLInitialization();
	static void GlfwWindowJudge(GLFWwindow* window);
	static void GammaCorrectionControl(bool flga);
	static GLFWwindow* CreateWindow(int width, int high, const char* name);
};

