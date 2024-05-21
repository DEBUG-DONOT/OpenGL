#pragma once
#include<string>
#include<vector>
#include<unordered_map>
/*
* ������Ϸ�ڵ�����Ҫ�̳е���
* ����add component�ĺ���
*/
class Component;
class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;
	Component* AddComponent(std::string component_name);
private:
	std::string name;
	std::unordered_map<std::string, std::vector<Component*>> typeName_Component_map;

};

