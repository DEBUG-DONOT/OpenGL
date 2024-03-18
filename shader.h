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
	void UpLoadUniformMat4(const std::string& name, const glm::mat4& m_matrix);
	void UpLoadUniformMat3(const std::string& name, const glm::mat3& m_matrix);
	void UpLoadUniformInt(const std::string& name, const int num);
	void UPLoadUniformFloat2(const std::string& name, const glm::vec2& m_vec2);
	void UpLoadUniformFloat3(const std::string& name, const glm::vec3& m_vec3);
	void UpLoadUniformFloat4(const std::string& name, const glm::vec4& m_vec3);
private:
	GLuint mShaderID;

};