#pragma once
#include "MathUtils.h"
#include <vector>
#include "GL/glut.h"

struct LightData {
	LightData() {}
	Vector4 ambient, diffuse, specular;
};

class Light 
{
public:
	Light() {}
	Vector4 position;
	LightData* lightData;
	void Render() {
		glLightfv(GL_LIGHT0, GL_AMBIENT, &(lightData->ambient.x));
		glLightfv(GL_LIGHT0, GL_SPECULAR, &(lightData->specular.x));
		glLightfv(GL_LIGHT0, GL_DIFFUSE, &(lightData->diffuse.x));
		glLightfv(GL_LIGHT0, GL_POSITION, &(position.x));
	}
};

class LightingManager
{
public:
	static LightingManager* instance;
	LightingManager() {
		if (instance == nullptr)
			instance = this;
		else
			delete(this);
	}


	std::vector<Light*> allLights;
	
	void RenderAllLights()
	{
		for (size_t i = 0; i < this->allLights.size(); i++)
		{
			allLights[i]->Render();
		}
	}

	void AddLight(Vector4 position, Vector4 ambient, Vector4 diffuse, Vector4 specular)
	{
		LightData* data = new LightData();
		data->ambient = ambient;
		data->diffuse = diffuse;
		data->specular = specular;

		Light* newLight = new Light();
		newLight->lightData = data;
		newLight->position = position;

		allLights.push_back(newLight);
	}
	

};

