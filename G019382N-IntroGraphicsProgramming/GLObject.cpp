#include "GLObject.h"

GLObject::GLObject()
{
}

GLObject::GLObject(Vector3 pos, Vector3 scale, GLuint textureID, std::vector<Mesh*> meshes, EventHandler* displayEvent)
{
	this->Transform.Position = pos;
	this->Transform.Scale = scale;
	render3D = new Renderer3D(displayEvent, this);
	render3D->SetTexture(textureID);
	render3D->objectMeshes = meshes;
}




