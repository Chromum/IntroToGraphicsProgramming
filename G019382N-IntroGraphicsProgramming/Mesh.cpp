#include "Mesh.h"

void Mesh::AddVert(Vector3* v3)
{
	verts.push_back(v3);
}

void Mesh::AddTextureUV(Vector2* v2)
{
	textureUVs.push_back(v2);
}

Mesh::Mesh() {

}

Mesh::~Mesh()
{
	for (int i = 0; i < verts.size(); i++)
	{
		delete verts[i];
	}
}

Mesh::Mesh(Primatives type) 
{
	//AddVert(.5f, .5f, -.5f);
	//AddVert(-.5f, .5f, -.5f);
	//AddVert(-.5f, .5f, .5f);
	//AddVert(.5f, .5f, .5f);

	//AddVert(.5f, -.5f, .5f);
	//AddVert(-.5f, -.5f, .5f);
	//AddVert(-.5f, -.5f, -.5f);
	//AddVert(.5f, -.5f, -.5f);

	//AddVert(.5f, .5f, .5f);
	//AddVert(-.5f, .5f, .5f);
	//AddVert(-.5f, -.5f, .5f);
	//AddVert(.5f, -.5f, .5f);

	//AddVert(.5f, -.5f, -.5f);
	//AddVert(-.5f, -.5f, -.5f);
	//AddVert(-.5f, .5f, -.5f);
	//AddVert(.5f, .5f, -.5f);

	//AddVert(-.5f, .5f, .5f);
	//AddVert(-.5f, .5f, -.5f);
	//AddVert(-.5f, -.5f, -.5f);
	//AddVert(-.5f, -.5f, .5f);

	//AddVert(.5f, .5f, -.5f);
	//AddVert(.5f, .5f, .5f);
	//AddVert(.5f, -.5f, .5f);
	//AddVert(.5f, -.5f, -.5f);
}
