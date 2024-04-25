#pragma once
#include "Renderer3D.h"
#include <vector>
#include "MathUtils.h"

using namespace std;

class GLObject
{
public:
	GLObject(Vector3 pos, Vector3 scale, GLuint textureID, std::vector<Mesh*> meshes, EventHandler* displayEvent);
	Transform Transform;
	Renderer3D* render3D = nullptr;

};



