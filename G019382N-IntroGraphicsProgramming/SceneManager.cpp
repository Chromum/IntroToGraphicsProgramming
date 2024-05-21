#include "SceneManager.h"
#include "ImageReader.h"
#include "Camera.h"
#include "Sphere.h"
#include "LinkedList.h"

SceneManager* SceneManager::instance;

SceneManager::SceneManager() {
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

SceneObject* SceneManager::FindObject(std::string name) {
	return sceneGraph->graph->GetObjectByName(name, sceneGraph->graph->head);
}

void SceneManager::CreateNewObject(SceneObject* object)
{
	sceneGraph->AddChild(object);

	if (GLObject* q = dynamic_cast<GLObject*>(object))
		Renderables.push_back(q);

	objectCount++;
}

void SceneManager::CreateNewObject(SceneObject* object, SceneObject* parente)
{
	parente->AddChild(object);
	if (GLObject* q = dynamic_cast<GLObject*>(object))
		Renderables.push_back(q);

	object->parent = parente;
	objectCount++;
}

void SceneManager::ToggleSkyboxTexture()
{
	GLObject* skybox = dynamic_cast<GLObject*>(FindObject("Skybox"));

	if (skybox->render3D->objectMeshes[0]->texture != this->skyboxId2)
		skybox->render3D->objectMeshes[0]->texture = this->skyboxId2;

	else if (skybox->render3D->objectMeshes[0]->texture != this->skyboxId1)
		skybox->render3D->objectMeshes[0]->texture = this->skyboxId1;
}

void SceneManager::ToggleWireFrame() {
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

void SceneManager::ToggleControls() {
	showControls = !showControls;
	std::cout << "CONTROL";
}

std::vector<GLObject*> SceneManager::GetAllObjects()
{
	return sceneGraph->graph->GetAllObjects(sceneGraph->graph->head);
}

void SceneManager::Update()
{
	for (size_t i = 0; i < Renderables.size(); i++)
	{
		Renderables[i]->Update();
	}
}

void SceneManager::SelectObject(float x, float y) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	Vector3 forward = (Camera::instance->lookat_point - Camera::instance->Transform.Position).Normilized();


	for (size_t i = 0; i < this->Renderables.size(); i++)
	{
		InterReturn r = this->Renderables[i]->selectionSphere->CheckIfIntersect(Camera::instance->Transform.Position, forward);
		if (r.result)
		{
			std::cout << "Hit the sphere:" << this->Renderables[i]->name << std::endl;
			this->selectedObject->selectionSphere->isSelected = false;
			this->selectedObject = Renderables[i];
			this->selectedObject->selectionSphere->isSelected = true;


		}
		else
		{
		}
	}
}