#pragma once
#include "MathUtils.h"
#include <vector>
#include "GL/freeglut.h"


enum Primatives { Cube };
struct MaterialData;

class Mesh
{
public:
	Mesh();
	~Mesh();
	Mesh(Primatives type);
	GLuint texture;
	MaterialData* matData;
	std::vector<Vector3*> verts;
	std::vector<Vector2*> textureUVs;
	std::vector<Vector2*> normals;
	std::vector<unsigned int> indicies = std::vector<unsigned int>();
	std::vector<unsigned int> UVindicies = std::vector<unsigned int>();
	std::vector<unsigned int> Normalindicies = std::vector<unsigned int>();
	void AddVert(Vector3* v3);
	void AddTextureUV(Vector2* v2);
	bool isQuadMesh;
};

