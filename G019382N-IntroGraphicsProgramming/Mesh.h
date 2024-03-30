#pragma once
#include "MathUtils.h"
#include <vector>

enum Primatives { Cube };

class Mesh
{
public:
	Mesh();
	~Mesh();
	Mesh(Primatives type);
	std::vector<Vector3*> verts;
	std::vector<Vector2*> textureUVs;
	std::vector<unsigned int> indicies = std::vector<unsigned int>();
	void AddVert(Vector3* v3);
	void AddTextureUV(Vector2* v2);
	bool isQuadMesh;
};

