#pragma once
#include "MathUtils.h"
#include "SceneObject.h"

struct InterReturn {
	bool result;
	Vector3 v1;
	Vector3 v2;
};

class GLObject;


class Sphere : public SceneObject
{
public:
	Sphere(float Rad, GLObject* par, std::string sphereName) : SceneObject(sphereName) {
		Radius = Rad;
		parent = par;
	}
	GLObject* parent;
	float Radius;
	bool isSelected = false;
	void Draw();
	InterReturn CheckIfIntersect(Vector3 rayStart, Vector3 rayDirection);
};

