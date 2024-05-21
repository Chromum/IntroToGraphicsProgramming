#pragma once
#include <vector>
#include <iostream>

class GLObject;
class SceneObject;
struct Vector3;

class SceneManager {
public:
	SceneManager();
	static SceneManager* instance;
	SceneObject* sceneGraph;
	GLObject* selectedObject;
	int objectCount = 0;
	bool wireFrame = false;
	bool showSelectionSpheres;
	bool showControls;
	int skyboxId1, skyboxId2;
	float deltaTime;
	std::vector<GLObject*> Renderables;
	std::vector<std::pair<Vector3, Vector3>> debugLines = std::vector<std::pair<Vector3, Vector3>>();


	SceneObject* FindObject(std::string name);

	void CreateNewObject(SceneObject* object);

	void CreateNewObject(SceneObject* object, SceneObject* parent);

	void ToggleSkyboxTexture();

	void ToggleWireFrame();

	void ToggleControls();

	std::vector<GLObject*> GetAllObjects();

	void Update();

	void SelectObject(float x, float y);

};
