#pragma once
#include <iostream>
#include "MathUtils.h"

class LinkedList;

class SceneObject
{
public:
	SceneObject(std::string name) {
		this->name = name;
	};
	Vector3 LocalPos;
	SceneObject* parent;
	std::string name;
	LinkedList* graph;
	Transform Transform;
	virtual void Update() {
		return;
	}
	void AddChild(SceneObject* child);
	void ToggleSkyboxTexture();
};

