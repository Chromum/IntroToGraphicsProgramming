#pragma once
#include "Mesh.h"
#include <iostream>
#include <map>

struct Vector4;

struct MaterialData {
public:
	std::map<std::string, int> textureList;
	Vector4 ambient, diffuse, specular;
	float opticalDensity;
	void LoadMaterialFile(std::string fileName);
};

class ModelLoader
{
public:
	std::vector<Mesh*> LoadMeshAtPath(std::string path);
	Vector3* LoadLine(std::string line, int startPoint);
	Vector2* LoadLineV2(std::string line, int startPoint);
	bool LoadLineInt(std::string line, int startPoint, std::vector<unsigned int>* vector, std::vector<unsigned int>* vector2, std::vector<unsigned int>* vector3);
};

