#pragma once
#include "Object.h"

struct InterReturn {
	bool result;
	Vector3 v1;
	Vector3 v2;
};


class Sphere : public Object
{
public:
	float Radius;
	void Draw(Vector3 col);
	InterReturn CheckIfIntersect(Vector3 rayStart, Vector3 rayDirection);
};

