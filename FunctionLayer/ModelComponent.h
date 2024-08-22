#pragma once
#include"../ResourseManager/model.h"
class ModelComponent :public Component
{
    /*
    * 这个模块调用了model
    */
public:
    ModelComponent() = default;
    virtual ~ModelComponent();
    bool LoadModel(std::string path);
    void Draw(Shader& shd);
    void ShowAllTextureType();
private:
    Model* modelPointer = nullptr;
};