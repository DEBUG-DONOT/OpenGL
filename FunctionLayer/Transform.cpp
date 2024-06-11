#include "Transform.h"
#include"rttr/registration.h"
using namespace rttr;

//property(name,getter,setter)
RTTR_REGISTRATION
{
	registration::class_<TransformComponent>("Transform")
	.constructor<>()//注意，这里给的是object，但是示例里面给的是指针,方括号里面给的是构造函数的参数类型
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
