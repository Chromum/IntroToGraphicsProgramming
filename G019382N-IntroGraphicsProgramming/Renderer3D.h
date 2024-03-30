#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include "GLUTUtils.h"
#include "Mesh.h"
#include <utility>
#include "EventHandler.h"
#include "Image.h"

class GLObject;
struct GlutColor;

class Renderer3D
{
public:
	Renderer3D(GLObject* object);
	GLObject* object;
	Image texture;
	Mesh* objectMesh;
	GlutColor color;
	Renderer3D(EventHandler* handler, GLObject* object);
	void RenderUpdate();
	void SetTexture(Image* image);
};

