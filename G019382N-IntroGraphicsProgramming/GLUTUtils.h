#pragma once
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"

struct GlutColor {
public:
	GlutColor() {
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
		a = 0.0f;
	};
	GLfloat r,g,b,a;
};
