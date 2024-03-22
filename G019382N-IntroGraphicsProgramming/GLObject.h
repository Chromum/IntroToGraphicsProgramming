#pragma once
#include "Renderer3D.h"
#include <vector>
#include "MathUtils.h"

using namespace std;

class GLObject
{
public:
	GLObject();
	Transform Transform;
	Renderer3D* render3D;

};



