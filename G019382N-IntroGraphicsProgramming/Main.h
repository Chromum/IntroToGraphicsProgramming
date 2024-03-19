#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include "GL2D.h"
#include "GL3D.h"
#include <utility>
#include <algorithm>
#include <iostream>
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
	//Display
	void Display();
	//KeyboardInput
	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void HandleInput();
	//Key Buffer
private:
	float rotationX;
	float rotationY;
	float rotationZ;
	bool buffer[256];
};

