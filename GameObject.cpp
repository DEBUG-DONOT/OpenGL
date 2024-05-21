#include "GameObject.h"
#include"rttr/registration.h"
#include"Component.h"
Component* GameObject::AddComponent(std::string component_name)
{
	rttr::type t = rttr::type::get_by_name(component_name);
	Component* component_=nullptr;
	if (t.is_valid())
	{
		rttr::variant v = t.create();
		component_ = v.get_value<Component*>();
		component_->SetGameObjecPointer(this);
		if (this->typeName_Component_map.find(component_name) != typeName_Component_map.end())
		{
			//рясп
			typeName_Component_map[component_name].push_back(component_);
		}
		else
		{
			typeName_Component_map[component_name] = std::vector<Component*>{ component_ };
		}
	}
	return component_;
}
