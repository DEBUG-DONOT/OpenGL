#ifndef MODEL_H
#define MODEL_H
#include "mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include"../shader.h"
#include"../FunctionLayer/Component.h"
class Model
{
    public:
        /*  模型数据  */
        vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        vector<Mesh> meshes;
        std::string directory;
        /*  函数   */
        Model(string path)
        {
            loadModel(path);
        }
        Model();
        virtual ~Model()=default;
        void Draw(Shader& shader);   
        void Draw(GLuint shader);
        void DrawPBR(Shader& shader);
        void loadModel(std::string path);
        void checkAllTypeTexture();
    private:
        /*  函数   */
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
            string typeName, vector<bool> *bRepeats = nullptr);
        unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);
        //用来查看有多少种类的texture
        unordered_set<std::string> allTypeTexture;
};



#endif