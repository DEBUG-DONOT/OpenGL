#include "GameObject.h"
#include"rttr/registration.h"
#include"Component.h"
Component* GameObject::AddComponent(std::string component_name)
{
	rttr::type t = rttr::type::get_by_name(component_name);
	Component* component_=nullptr;
	Component temp;
	if (t.is_valid())
	{
		rttr::variant v = t.create();//创建一个instance
		temp = v.get_value<Component>();
		//component_ = v.get_value<Component*>();//
		component_ = &temp;
		component_->SetGameObjecPointer(this);
		if (this->typeName_Component_map.find(component_name) != typeName_Component_map.end())
		{
			//已有
			typeName_Component_map[component_name].push_back(component_);
		}
		else
		{
			typeName_Component_map[component_name] = std::vector<Component*>{ component_ };
		}
	}
	return component_;
}

Component* GameObject::GetComponentByName(std::string component_name)
{
	if (this->typeName_Component_map.find(component_name)!=typeName_Component_map.end())
	{
		//有
		return typeName_Component_map[component_name][0];
	}
	return nullptr;
}

std::vector<Component*> GameObject::GetComponents(std::string component_name)
{
	if (this->typeName_Component_map.find(component_name) != typeName_Component_map.end())
	{
		//有
		return typeName_Component_map[component_name];
	}
	return std::vector<Component*>();
}
