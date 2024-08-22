#pragma once
#include"../ResourseManager/model.h"
class ModelComponent :public Component
{
    /*
    * ���ģ�������model
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