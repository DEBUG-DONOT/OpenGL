#pragma once
#include<string>
#include"shader.h"
#include<vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class Model
{
public:

	void loadModel(std::string path);
	void Draw(Shader shader);

private:


};