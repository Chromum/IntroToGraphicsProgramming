#pragma once
#include <iostream>
#include "EventHandler.h"#
using namespace std;

class GLObject;

class GLComponent
{
public:
	GLComponent();
	GLObject* GetParent();
	GLObject* objectParent;
	string name;
	int id;

};

