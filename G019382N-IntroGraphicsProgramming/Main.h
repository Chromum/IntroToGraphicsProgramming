#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include "GL2D.h"
#include "GL3D.h"
#include <utility>
#define REFRESHRATE 16

using namespace std;


class Main
{
public:
	int main(int argc, char* argv[]);
	//Construct
	Main(int argc, char* argv[]);
	//Deconstruct
	~Main(void);
	//Update
	void Update();
	
	///////
	void Display();
private:
	float rotation;
};

