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
private:
    Model* modelPointer = nullptr;
};