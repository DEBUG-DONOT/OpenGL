#include"ModelComponent.h"
#include<rttr/registration.h>
#include"../shader.h"
#include<iostream>
ModelComponent::~ModelComponent()
{
    if (this->modelPointer)
    {
        delete modelPointer;
    }
}

bool ModelComponent::LoadModel(std::string path)
{
    if (!modelPointer)//第一次
    {
        modelPointer = new Model(path);
    }
    return modelPointer != nullptr;
}

void ModelComponent::Draw(Shader& shd)
{
    if (modelPointer != nullptr)
    {
        modelPointer->Draw(shd);
    }
    else
    {
        std::cerr << "model Pointer is nullptr" << std::endl;
    }
}

void ModelComponent::ShowAllTextureType()
{
    if (this->modelPointer == nullptr)
    {
        cout << "model pointer is nullptr";
        return;
    }
    this->modelPointer->checkAllTypeTexture();
}

RTTR_REGISTRATION
{
     rttr::registration::class_<ModelComponent>("ModelComponent")
    .constructor<>()//注意，这里给的是object，但是示例里面给的是指针,方括号里面给的是构造函数的参数类型
    .method("LoadModel",&ModelComponent::LoadModel)
    .method("Draw",&ModelComponent::Draw);
}
