#pragma once
#include "Vector3.h"
#include "GL3D.h"



class Object
{
public:
	struct{
		Vector3 Position;
		Vector3 Rotation;
		Vector3 Scale;
	} Transform;

	//Temp
	enum ObjectType { Cube, NULL} renderType;
	

	void RenderObject();


};

