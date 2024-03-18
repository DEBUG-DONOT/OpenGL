#pragma once
#include<string>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
class BasicShader
{
public:
	BasicShader(std::string path);
	inline const std::string GetCode() { return code; }
private:
	void ReadCodeFromFile(std::string path);
	std::string path;
	std::string code;
};

class VertexShader:public BasicShader
{
public:
	//顶点着色器
	VertexShader(const std::string path)
		:BasicShader(path)
	{}
};

class FragmentShader:public BasicShader
{
	//片段着色器
public:
	FragmentShader(const std::string path)
		:BasicShader(path)
	{}
};

class Shader
{
public:
	Shader(VertexShader vs,FragmentShader fs);
	virtual ~Shader();
	void Bind();
	void UnBind();
private:
	GLuint mShaderID;

};