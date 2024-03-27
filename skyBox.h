#pragma once
#include "Texture.h"
#include "shader.h"
#include "Camera.h"
//这个类只需要给出一个shader就能画出一个天空盒，甚至不需要专门引入shader
class skyBox
{
public:
	skyBox(float* box,std::vector<std::string>& texturPath);
	void Draw(const Camera& camera);
private:
	void setup(float* box);
	unsigned int vao, vbo;
	std::vector<std::string> texturPath;
	Shader* shader=nullptr;
	CubeTexture* texture=nullptr;
	bool InitialShader = false;
	std::string vertShader="ShaderLib/skyBoxVert.glsl";
	std::string fragShader="ShaderLib/skyBoxFrag.glsl";
};