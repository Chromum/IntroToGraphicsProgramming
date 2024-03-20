#pragma once
#include "MathUtils.h"
#include <vector>

class Mesh
{
public:
	std::vector<Vector3> verts;
	void AddVert(float x,float y,float z);
};

