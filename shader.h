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
	//������ɫ��
	VertexShader(const std::string path)
		:BasicShader(path)
	{}
};

class FragmentShader:public BasicShader
{
	//Ƭ����ɫ��
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