#pragma once
#include "Texture.h"
#include "shader.h"
#include "Camera.h"
//�����ֻ��Ҫ����һ��shader���ܻ���һ����պУ���������Ҫר������shader
class skyBox
{
public:
	/*
	* @param box ��պ�����
	* @param texturePath ����·��
	*/
	skyBox(float* box,std::vector<std::string>& texturePath);
	skyBox(std::vector<std::string>& texturePath);
	void Draw(const Camera& camera);
private:
	static float* standarVertex ;
	void setup(float* box);
	unsigned int vao, vbo;
	std::vector<std::string> texturePath;
	Shader* shader=nullptr;
	CubeTexture* texture=nullptr;
	bool InitialShader = false;
	std::string vertShader="ShaderLib/skyBoxVert.glsl";
	std::string fragShader="ShaderLib/skyBoxFrag.glsl";
    
};