#include"Camera.h"
#include<glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 pos, glm::vec3 lookat, glm::vec3 up)
{
	this->view = glm::lookAt(pos, lookat, up);
	this->model = glm::mat4(1.0f);
	cameraFront = glm::normalize(lookat - pos); 
	cameraUp = glm::normalize(up);
	cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
}

void Camera::SetScene(float fov, float aspect, float near, float far)
{
	this->aspect = aspect;
	this->fov = fov;
	this->near = near;
	this->far = far;
	this->projection = glm::perspective(fov, aspect, near, far);
}

void Camera::ProcessInput(GLFWwindow* window,float deltaTime)
{
	float cameraSpeed = speed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		;
}




