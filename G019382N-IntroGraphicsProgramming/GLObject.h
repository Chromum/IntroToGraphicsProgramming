#pragma once
#include "Renderer3D.h"
#include <vector>
#include "MathUtils.h"

class LinkedList;

using namespace std;

class GLObject
{
public:
	GLObject();
	GLObject(Vector3 pos, Vector3 scale, std::vector<Mesh*> meshes, EventHandler* displayEvent);
	LinkedList* graph;
	Transform Transform;
	Renderer3D* render3D = nullptr;

};



