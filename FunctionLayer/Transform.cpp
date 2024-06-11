#include "Transform.h"
#include"rttr/registration.h"
using namespace rttr;

//property(name,getter,setter)
RTTR_REGISTRATION
{
	registration::class_<TransformComponent>("Transform")
	.constructor<>()//ע�⣬���������object������ʾ�����������ָ��,��������������ǹ��캯���Ĳ�������
	.property("position",&TransformComponent::GetPosition,&TransformComponent::SetPosition)
	.property("transpose",&TransformComponent::GetTranspose,&TransformComponent::SetTranspose)
	.property("scale",&TransformComponent::GetScale,&TransformComponent::SetScale);
}

TransformComponent::TransformComponent()
	:position(0.0),transpose(0.0),scale(1.0)
{
}

TransformComponent::~TransformComponent()
{
}
