#pragma once
#include "GLComponent.h"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include "GLUTUtils.h"
#include "Mesh.h"
#include <utility>


class Render3DComponent : public GLComponent 
{
public:
	Mesh objectMesh;
	Render3DComponent(EventHandler* handler);
	void RenderUpdate();
	

};

