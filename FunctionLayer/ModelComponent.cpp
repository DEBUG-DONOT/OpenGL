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
    if (!modelPointer)//��һ��
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
    .constructor<>()//ע�⣬���������object������ʾ�����������ָ��,��������������ǹ��캯���Ĳ�������
    .method("LoadModel",&ModelComponent::LoadModel)
    .method("Draw",&ModelComponent::Draw);
}
