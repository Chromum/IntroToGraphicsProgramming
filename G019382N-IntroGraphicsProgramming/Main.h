#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include <utility>
using namespace std;

class Main
{
public:
	int main(int argc, char* argv[]);
	//Construct
	Main(int argc, char* argv[]);
	//Deconstruct
	~Main(void);
	
	///////
	void Display();
	void DrawPolygon();
	void DrawTriangle(pair<GLfloat,GLfloat> p1, pair<GLfloat, GLfloat> p2, pair<GLfloat, GLfloat > p3 );
};

