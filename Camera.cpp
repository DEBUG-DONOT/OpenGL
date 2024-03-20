#include"Camera.h"
#include<glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 pos, glm::vec3 lookat, glm::vec3 up)
	:pos(pos),lookat(lookat),up(up)
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
		//this->model = glm::translate(this->model, this->cameraFront * -cameraSpeed);
		this->pos += this->cameraFront * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		//this->model = glm::translate(this->model, this->cameraFront * cameraSpeed);
		this->pos -= this->cameraFront * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		//this->model = glm::translate(this->model, this->cameraRight * cameraSpeed);
		this->pos -= this->cameraRight * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		//this->model = glm::translate(this->model, this->cameraRight * -cameraSpeed);
		this->pos += this->cameraRight * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		//this->model = glm::translate(this->model, this->cameraUp * -cameraSpeed);
		this->pos += this->cameraUp * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		//this->model = glm::translate(this->model, this->cameraUp * cameraSpeed);
		this->pos -= this->cameraUp * cameraSpeed;
	this->view= glm::lookAt(pos, pos+cameraFront, up);
}




