#pragma once
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<GLFW/glfw3.h>
class Camera
{
public:
	Camera(glm::vec3 pos, glm::vec3 lookat, glm::vec3 up);
	void SetScene(float fov, float aspect, float near, float far);
	inline glm::mat4 GetModelMatrix() const { return model; }
	inline glm::mat4 GetViewMatrix() const { return view; }
	inline glm::mat4 GetProjectionMatrix() const { return projection; }
	inline glm::mat4 GetMVP() const { return projection * view * model; }
	inline void SetModelMatrix(glm::mat4 model) { this->model = model; }
	inline glm::vec3 GetCameraPos()const { return pos; }
	//�ƶ�����
	void ProcessInput(GLFWwindow* window, float deltaTime);
private:
	float aspect,fov,near, far,speed=1.0f;
	glm::mat4 model, view, projection;
	glm::vec3 pos, lookat, up;
	glm::vec3 cameraFront, cameraRight, cameraUp;

};

class Light
{
public:
	Light(glm::vec3 position, glm::vec3 direction, glm::vec3 color);
	inline glm::vec3 GetDir() const { return lightDir; }
	inline glm::vec3 GetPos() const { return lightPos; }
	inline glm::vec3 GetColor() const { return lightColor; }
private:
	glm::vec3 lightDir, lightPos, lightColor;
	glm::vec3 kNum;//��һ��vec����ʾ���Դ��ϵ������һ����Ӧ��������������ֱ��Ӧһ����Ͷ�����
};