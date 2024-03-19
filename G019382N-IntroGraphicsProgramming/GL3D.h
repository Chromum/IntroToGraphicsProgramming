#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include "GLUTUtils.h"
#include <utility>
using namespace std;


class GL3D
{
public:
	void DrawCube();
	void DrawCubeRotate(float rotationX, float rotationY, float rotationZ);

};

