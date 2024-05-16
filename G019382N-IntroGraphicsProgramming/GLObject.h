#pragma once
#include "Renderer3D.h"
#include <vector>
#include "MathUtils.h"
#include "SceneObject.h"
#include "Sphere.h"

class LinkedList;

using namespace std;

class GLObject : public SceneObject
{
public:
	GLObject(std::string name) : SceneObject(name) {}
	GLObject(std::string name, Vector3 pos, Vector3 scale, std::vector<Mesh*> meshes, EventHandler* displayEvent, float selectSphereRadius) : SceneObject(name) {
		this->Transform.Position = pos;
		this->Transform.Scale = scale;
		render3D = new Renderer3D(displayEvent, this);
		render3D->objectMeshes = meshes;
		this->selectionSphere = new Sphere(selectSphereRadius, this);
	}
	Renderer3D* render3D = nullptr;
	Sphere* selectionSphere;
	void Update() override;

};



