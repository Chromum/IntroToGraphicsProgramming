#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include "GL2D.h"
#include "GL3D.h"
#include "GLObject.h";
#include "Renderer3D.h"
#include <utility>
#include <algorithm>
#include <iostream>
#include "EventHandler.h"
#include <vector>

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
	void ReBuildProjectionMatrix();
	
	//Event Handlers
	EventHandler* displayEvent = new EventHandler("Display");

	//TestObject
	vector<GLObject*> objects;

	//Input
	Vector2 mouseDelta = Vector2(0,0);
	bool leftMouse;
	bool rightMouse;
	bool middleMouse;

	//Screen
	int screenWidth;
	int screenHeight;

	Transform cameraTransform;
	Vector3 cameraFront;

	//Camera
	
private:
	float rotationX;
	float rotationY;
	float rotationZ;
	bool buffer[256];


};

