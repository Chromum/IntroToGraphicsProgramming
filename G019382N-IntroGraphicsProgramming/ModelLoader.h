#pragma once
#include "Mesh.h"
#include <iostream>

class ModelLoader
{
public:
	Mesh* LoadMeshAtPath(std::string path);
	Vector3* LoadLine(std::string line, int startPoint);
	void LoadLineInt(std::string line, int startPoint, std::vector<unsigned int>* vector);
};

