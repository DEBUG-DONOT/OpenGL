#include "Transform.h"
#include"rttr/registration.h"
using namespace rttr;

//property(name,getter,setter)
RTTR_REGISTRATION
{
	registration::class_<Transform>("Transform")
	.constructor<>()//ע�⣬���������object������ʾ�����������ָ��
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
