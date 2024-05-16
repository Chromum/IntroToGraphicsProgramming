#pragma once
#include "LinkedList.h"
#include <iostream>
#include "ImageReader.h"
#include "Camera.h"

class SceneManager {
public:
	static SceneManager* instance;
	SceneObject* sceneGraph;
	SceneObject* selectedObject;
	int objectCount = 0;
	bool wireFrame = false;
	bool showSelectionSpheres;
	bool showControls;
	int skyboxId1, skyboxId2;
	std::vector<GLObject*> Renderables;

	SceneManager() {
		if (instance == nullptr)
		{
			instance = this;
			sceneGraph = new SceneObject("Level");
			sceneGraph->graph = new LinkedList(sceneGraph);
			objectCount++;
			skyboxId2 = ImageReader().ReadImage("Models/skybox_texture2.png");

		}
		else
			delete(this);
	}

	SceneObject* FindObject(std::string name) {
		return sceneGraph->graph->GetObjectByName(name,sceneGraph->graph->head);
	}

	void CreateNewObject(SceneObject* object)
	{
		sceneGraph->AddChild(object);

		if (GLObject* q = dynamic_cast<GLObject*>(object))
			Renderables.push_back(q);

		objectCount++;
	}

	void CreateNewObject(SceneObject* object, SceneObject* parent)
	{
		parent->AddChild(object);
		if (GLObject* q = dynamic_cast<GLObject*>(object))
			Renderables.push_back(q);
		objectCount++;
	}

	void ToggleSkyboxTexture()
	{
		GLObject* skybox = dynamic_cast<GLObject*>(FindObject("Skybox"));

		if (skybox->render3D->objectMeshes[0]->texture != this->skyboxId2)
			skybox->render3D->objectMeshes[0]->texture = this->skyboxId2;

		else if (skybox->render3D->objectMeshes[0]->texture != this->skyboxId1)
			skybox->render3D->objectMeshes[0]->texture = this->skyboxId1;
	}

	void ToggleWireFrame() {
		if (wireFrame)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		wireFrame = !wireFrame;
	}

	void ToggleControls() {
		showControls = !showControls;
		std::cout << "CONTROL";
	}

	std::vector<GLObject*> GetAllObjects() 
	{
		return sceneGraph->graph->GetAllObjects(sceneGraph->graph->head);
	}

	void Update() 
	{
		for (size_t i = 0; i < Renderables.size(); i++)
		{
			Renderables[i]->Update();
		}
	}

	std::pair<Vector3,Vector3> SelectObject() {
		GLfloat viewMatrix[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix);

		Vector3 cf = Vector3(-viewMatrix[2], -viewMatrix[6], -viewMatrix[10]);

		for (size_t i = 0; i < this->Renderables.size(); i++)
		{
			InterReturn r = this->Renderables[i]->selectionSphere->CheckIfIntersect(Camera::instance->Transform.Position, cf);
			if (r.result)
			{
				std::cout << "Hit the sphere:" << this->Renderables[i]->name << std::endl;
			}
			else
			{
				std::cout << "Missed the sphere:" << this->Renderables[i]->name << std::endl;
			}
		}

		return std::pair<Vector3, Vector3>(Camera::instance->Transform.Position, cf * 100);

		


	}
};
