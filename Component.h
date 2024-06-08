#pragma once

class GameObject;
class Component
{
public:
	Component() = default;
	virtual ~Component() = default;
	virtual void tick();
	void SetGameObjecPointer(GameObject* gop);
	GameObject* GetGameObjectPointer();
private:
	GameObject* gameObject_=nullptr;

};