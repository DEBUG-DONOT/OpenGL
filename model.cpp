#include"model.h"
#include<iostream>
#include<stb_image.h>
void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	this->scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_not_of('/'));
    ProcessNode(scene->mRootNode,scene);
}

unsigned int Model::TextureFromFile(const char* str, const std::string& dic)
{
    std::string fileName = std::string(str);
    fileName = dic + '/' + fileName;
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
    //std::cout << nrChannels << std::endl;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    if (data)
    {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
    //stbi_image_free(data);
    return textureID;
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    for (int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        Meshes.push_back(ProcessMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> tempVertex;
    std::vector<unsigned int> tempIndex;
    std::vector<Texture> tempTexture;
    for (int i = 0; i < mesh->mNumVertices; i++)//处理vertex
    {
        Vertex vert;
        auto x = mesh->mVertices[i];
        glm::vec3 currVec;
        currVec.x = x.x;
        currVec.y = x.y;
        currVec.z = x.z;
        vert.position = currVec;
        currVec.x = mesh->mNormals[i].x;
        currVec.y = mesh->mNormals[i].y;
        currVec.z = mesh->mNormals[i].z;
        vert.normal = currVec;
        if (mesh->HasTextureCoords(0))
        {
            glm::vec2 tex;
            tex.x = mesh->mTextureCoords[0][i].x;
            tex.y = mesh->mTextureCoords[0][i].y;
            vert.TexCoord = tex;
        }
        else vert.TexCoord = glm::vec2(0, 0);
        tempVertex.push_back(vert);
    }
    for (int i = 0; i < mesh->mNumFaces; i++)//处理index
    {
        auto face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++)
        {
            tempIndex.push_back(face.mIndices[j]);
        }
    }
    if (mesh->mMaterialIndex >= 0)//处理texture
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMap = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        tempTexture.insert(tempTexture.end(), diffuseMap.begin(), diffuseMap.end());
        std::vector<Texture> specMap = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        tempTexture.insert(tempTexture.end(), specMap.begin(), specMap.end());
    }
    return Mesh(tempVertex, tempIndex, tempTexture);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture> tex;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        Texture t;
        t.id= TextureFromFile(str.C_Str(), directory);
        t.type = typeName;
        t.path = str;
        tex.push_back(t);
    }
    return tex;
}


Model::Model(std::string path)
{
    loadModel(path);
}

void Model::Draw(Shader shader)
{
    for(auto & curr:Meshes)
    {
        curr.Draw(shader);
    }
}

Mesh::Mesh(std::vector<Vertex> vts, std::vector<unsigned int> ids, std::vector<Texture> ts)
    :vertices(vts),indices(ids),textures(ts)
{
    SetUpMesh();
}

void Mesh::Draw(Shader shader)
{
    //todo
    int diffuseNr = 1;
    int specularNr = 1;
    for (int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name=="texture_specular")
            number = std::to_string(specularNr++);
        shader.UpLoadUniformInt("material." + name + number, i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}   

void Mesh::SetUpMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));

    glBindVertexArray(0);

}
