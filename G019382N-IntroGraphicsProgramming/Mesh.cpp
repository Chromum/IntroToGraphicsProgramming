#include "Mesh.h"

void Mesh::AddVert(float x, float y, float z)
{
	Vector3 toAdd = Vector3(x, y, z);
	verts.push_back(toAdd);
}
