#pragma once
#include"Component.h"
#include<glm/glm.hpp>
/*
* 表示位置
* 是一种组件
*/

class TransformComponent :public Component
{
public:
	TransformComponent();
	virtual ~TransformComponent();
	inline glm::vec3 GetPosition() const{ return position; }
	inline glm::vec3 GetTranspose() const{ return transpose; }
	inline glm::vec3 GetScale() const{ return scale; }
	inline void SetPosition(glm::vec3 newPos) { position = newPos; }
	inline void SetTranspose(glm::vec3 newTranspose) { transpose = newTranspose; }
	inline void SetScale(glm::vec3 newScale) { scale = newScale; }
private:
	glm::vec3 position;
	glm::vec3 transpose;
	glm::vec3 scale;
};


