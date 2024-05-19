#pragma once
#include "MathUtils.h"

struct InterReturn {
	bool result;
	Vector3 v1;
	Vector3 v2;
};

class GLObject;


class Sphere
{
public:
	Sphere(float Rad, GLObject* par) {
		Radius = Rad;
		parent = par;
	}
	Transform t;
	GLObject* parent;
	float Radius;
	bool isSelected;
	void Draw(Vector3 col);
	InterReturn CheckIfIntersect(Vector3 rayStart, Vector3 rayDirection);
};

