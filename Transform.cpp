#include "Transform.h"
#include"rttr/registration.h"
using namespace rttr;

//property(name,getter,setter)
RTTR_REGISTRATION
{
	registration::class_<Transform>("Transform")
	.constructor<>()//注意，这里给的是object，但是示例里面给的是指针
	.property("position",&Transform::GetPosition,&Transform::SetPosition)
	.property("transpose",&Transform::GetTranspose,&Transform::SetTranspose)
	.property("scale",&Transform::GetScale,&Transform::SetScale);
}

Transform::Transform()
{
}

Transform::~Transform()
{
}
