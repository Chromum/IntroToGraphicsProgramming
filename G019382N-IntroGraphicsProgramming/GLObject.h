#pragma once
#include "GLComponent.h"
#include <vector>
#include "MathUtils.h"

using namespace std;

class GLObject
{
public:
	GLObject();
	struct
	{
		Vector3 Position;
		Quaternion Rotation;
		Vector3 Scale;
	}Transform;
	void AddComponent(GLComponent* component);
	vector<GLComponent*> objectComponents;
};



