#pragma once
#include<string>
#include<vector>
#include<unordered_map>
#include <rttr/registration>
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

    template <class T>
    T* AddComponent() {
        T* component = new T();
        rttr::type t = rttr::type::get(*component);
        std::string component_type_name = t.get_name().to_string();
        component->SetGameObjecPointer(this);
        if (typeName_Component_map.find(component_type_name) == typeName_Component_map.end()) {
            std::vector<Component*> component_vec;
            component_vec.push_back(component);
            typeName_Component_map[component_type_name] = component_vec;
        }
        else {
            typeName_Component_map[component_type_name].push_back(component);
        }
        return component;
    }

	Component* GetComponentByName(std::string component_name);
	std::vector<Component*> GetComponents(std::string component_name);
private:
	std::string name;
	std::unordered_map<std::string, std::vector<Component*>> typeName_Component_map;

};

