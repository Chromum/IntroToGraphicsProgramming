#pragma once
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"

struct GlutColor {
public:
	GlutColor() {
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
		a = 1.0f;
	};
	GlutColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	};
	GLfloat r,g,b,a;
};
