#pragma once
#include<string>
#include<glad/glad.h>
#include<vector>
//class Texture
//{
//public:
//	Texture(std::string path);
//	void BindTexture();
//	void BindTexture(int i);
//	void UnBindTexture();
//private:
//	void Load_Texture(std::string path);
//	unsigned int textureID;
//};

class CubeTexture
{
public:
	CubeTexture(std::vector<std::string>& cubePath);
	void BindTexture();
	void UnBindTexture();
private:
	void LoadTexture(std::vector<std::string>& path);
	unsigned int textureID;
};