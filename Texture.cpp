#include "Texture.h"
#include<iostream>
//#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
//Texture::Texture(std::string path)
//{
//	Load_Texture(path);
//}
//
//void Texture::BindTexture()
//{
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, textureID);
//}
//
//void Texture::BindTexture(int i)
//{
//	glActiveTexture(GL_TEXTURE0 + i);
//	glBindTexture(GL_TEXTURE_2D, textureID);
//}
//
//void Texture::UnBindTexture()
//{
//	glBindTexture(GL_TEXTURE_2D, 0);
//}
//
//void Texture::Load_Texture(std::string path)
//{
//	//std::cout << path << std::endl;
//	glGenTextures(1, &textureID);
//	glBindTexture(GL_TEXTURE_2D, textureID);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	int width, height, nrChannels;
//	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
//	//std::cout << nrChannels << std::endl;
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//	glGenerateMipmap(GL_TEXTURE_2D);
//	if (data&&nrChannels==3)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else if (data && nrChannels == 4)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		std::cout << "Failed to load texture" << std::endl;
//	}
//	stbi_image_free(data);
//}

CubeTexture::CubeTexture(std::vector<std::string> cubePath)
{
	LoadTexture(cubePath);
}

void CubeTexture::BindTexture()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
}

void CubeTexture::UnBindTexture()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP,0);
}

void CubeTexture::LoadTexture(std::vector<std::string> path)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < path.size(); i++)
    {
        unsigned char* data = stbi_load(path[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            GLenum format;
            if (nrChannels == 1)
                format = GL_RED;
            else if (nrChannels == 3)
                format = GL_RGB;
            else if (nrChannels == 4)
                format = GL_RGBA;

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data); 
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << path[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}
