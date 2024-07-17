#include "Application.h"
#include<GLFW/glfw3.h>

double Application::currFrame = 0;
double Application::deltaTime = 0;
double Application::lastFrame = 0;

Application::~Application()
{
}

void Application::tick()
{
}

bool Application::AppInitialization()
{
	return false;
}

double Application::clockTick()
{
	currFrame = glfwGetTime();
	deltaTime = currFrame - lastFrame;
	lastFrame = currFrame;
	return deltaTime;
}

void Application::LogicTick()
{
}

void Application::RenderTick()
{
}
