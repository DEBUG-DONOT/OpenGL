#include"Component.h"

void Component::SetGameObjecPointer(GameObject* gop)
{
	this->gameObject_ = gop;
}

GameObject* Component::GetGameObjectPointer()
{
	return this->gameObject_;
}
