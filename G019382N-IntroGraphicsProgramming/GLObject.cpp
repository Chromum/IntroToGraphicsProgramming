#include "GLObject.h"

GLObject::GLObject()
{
	
}

void GLObject::AddComponent(GLComponent* component)
{
	objectComponents.push_back(component);
}



