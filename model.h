#pragma once
#include<string>
#include"shader.h"
#include<vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include<glad/glad.h>
#include"shader.h"


struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 TexCoord;
};
struct Texture
{
	unsigned int id;
	std::string type;
	aiString path;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	Mesh(std::vector<Vertex> vts, std::vector<unsigned int> ids, std::vector<Texture> ts);
	void Draw(Shader shader);

private:
	unsigned int VAO, VBO, EBO;
	void SetUpMesh();

};

class Model
{
public:
	Model(std::string path);
	void Draw(Shader shader);
private:
	void loadModel(std::string path);
	unsigned int TextureFromFile(const char* str, const std::string& dic);
	std::vector<Mesh> Meshes;
	std::string directory;
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	const aiScene* scene = nullptr;


};