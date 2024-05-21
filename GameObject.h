#pragma once
#include<string>
#include<vector>
#include<unordered_map>
/*
* 所有游戏内的物体要继承的类
* 包含add component的函数
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

