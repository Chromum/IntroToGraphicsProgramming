#include "GLComponent.h"
#include "GLObject.h"

GLComponent::GLComponent()
{
}

GLObject* GLComponent::GetParent()
{
	
	return objectParent;
}
