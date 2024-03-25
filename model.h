#ifndef MODEL_H
#define MODEL_H
#include "mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include"shader.h"
class Model 
{
    public:
        /*  模型数据  */
        vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        vector<Mesh> meshes;
        string directory;
        /*  函数   */
        Model(string path)
        {
            loadModel(path);
        }
        void Draw(Shader& shader);   
        void Draw(GLuint shader);
    private:
        
        /*  函数   */
        void loadModel(string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                             string typeName, vector<bool> *bRepeats = nullptr);
        unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);
};

#endif