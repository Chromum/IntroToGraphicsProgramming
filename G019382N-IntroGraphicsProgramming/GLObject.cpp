#include "GLObject.h"

void GLObject::Update()
{
	//if (this->render3D != nullptr)
	//	this->render3D->RenderUpdate();

	if (this->selectionSphere != nullptr)
		this->selectionSphere->Draw(Vector3(1,1,1));
}




