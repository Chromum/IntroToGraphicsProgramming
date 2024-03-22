#pragma once
#include "MathUtils.h"
#include <vector>

enum Primatives { Cube };

class Mesh
{
public:
	Mesh();
	Mesh(Primatives type);
	std::vector<Vector3> verts;
	void AddVert(float x,float y,float z);
};

