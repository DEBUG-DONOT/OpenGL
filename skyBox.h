#pragma once
#include "ResourseManager/Texture.h"
#include "shader.h"
#include "FunctionLayer/Camera.h"
//这个类只需要给出一个shader就能画出一个天空盒，甚至不需要专门引入shader
class skyBox
{
public:
	/*
	* @param box 天空盒数据
	* @param texturePath 纹理路径
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
	std::string vertShader="Resourse/ShaderLib/skyBoxVert.glsl";
	std::string fragShader="Resourse/ShaderLib/skyBoxFrag.glsl";
    
};