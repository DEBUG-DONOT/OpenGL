#include"Camera.h"
#include"GameObject.h"
#include"Transform.h"
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

Light::Light(glm::vec3 position, glm::vec3 direction, glm::vec3 color)
	:lightDir(direction),lightPos(position),lightColor(color)
{
}

std::vector<CameraComponent*> CameraComponent::CameraList;
CameraComponent* CameraComponent::currentCamera = nullptr;
CameraComponent::CameraComponent()
	:depth(0)
{
	if (CameraList.size() > 0)
	{
		auto d = CameraList.back()->depth + 1;
		depth = d;
	}
	CameraList.push_back(this);
}

CameraComponent::~CameraComponent()
{
	auto it = std::find(CameraList.begin(), CameraList.end(), this);
	if (it != CameraList.end()) CameraList.erase(it);
}

void CameraComponent::SetView(const glm::vec3& cameraFoward, const glm::vec3& cameraUp)
{
	auto temp = dynamic_cast<TransformComponent*>( this->GetGameObjectPointer()->GetComponentByName("Transform"));
	this->view = glm::lookAt(temp->GetPosition(), cameraFoward, cameraUp);
}

void CameraComponent::SetProjction(double fovDegrees, double aspectRatio, double nearClip, double farClip)
{
	this->projction = glm::perspective(fovDegrees, aspectRatio, nearClip, farClip);
}

void CameraComponent::clear()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//void CameraComponent::Foreach(std::function<void()> func)
//{
//}

void CameraComponent::SortCamera()
{
	//将vector中的camera按照深度从小到达排序
	std::sort(CameraComponent::CameraList.begin(), CameraList.end(), [](CameraComponent* c1, CameraComponent* c2)
		{return c1->depth < c2->depth; });
}