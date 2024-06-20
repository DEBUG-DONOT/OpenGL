#pragma once
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<GLFW/glfw3.h>
#include"Component.h"
#include<vector>
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
	//移动处理
	void ProcessInput(GLFWwindow* window, float deltaTime);
private:
	/*
	* aspect:宽高比
	* fov：filed of view
	* near far 近平面和远平面，裁剪平面
	*/
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
	glm::vec3 kNum;//用一个vec来表示点光源的系数，第一个对应常数项，后面两个分别对应一次项和二次项
};


class CameraComponent :public Component
{
public:
	CameraComponent();
	~CameraComponent();
	//inline void SetPosition(glm::vec3 pos) { position = pos; }
	inline glm::mat4 GetViewMatrix() { return view; }
	inline glm::mat4 GetProjctionMatrix() { return projction; }
	void SetView(const glm::vec3& cameraFoward,const glm::vec3& cameraUp);
	void SetProjction(double fovDegrees,double aspectRatio,double nearClip,double farClip);
	void clear();
private:
	int depth;//相机深度，所有的相机会从深度低的开始绘制，深度高的会在后面绘制,从0开始，-1表示未设置
	void SortCamera();
	glm::mat4 view;
	glm::mat4 projction;
	//glm::vec3 position;//从transform中获得
	//glm::vec3 lookAt;
	//glm::vec3 up;
	//double aspect;//宽高比
	//double nearPlane;
	//double farPlane;
	//double fov;//filed of view
	static std::vector<CameraComponent*> CameraList;
	static CameraComponent* currentCamera;
	
};

