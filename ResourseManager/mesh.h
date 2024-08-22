#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include"../shader.h"
#include<rttr/registration.h>
#define MAX_BONE_INFLUENCE 4

using namespace std;

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
    unsigned int id;
    string type;
    string path;    // 我们储存纹理的路径用于与其它纹理进行比较
    bool operator==(const Texture& other) const {
        return id == other.id && type == other.type && path == other.path;
    }
};

class Mesh {
    public:
        /*  网格数据  */
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;
        unsigned int VAO;
        /*  函数  */
        //容器内的类必须有默认构造函数
        Mesh() = default;
        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
        
        void Draw(Shader& shader);
        void Draw(GLuint shader);
        void DrawPBR(Shader& shader);
    private:
        /*  渲染数据  */
        unsigned int VBO, EBO;
        /*  函数  */
        void setupMesh();
};  

#endif