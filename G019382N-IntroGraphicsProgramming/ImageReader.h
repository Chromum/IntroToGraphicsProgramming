#pragma once
#include <iostream>
#include "GL/glut.h"

struct Image;

class ImageReader
{
public:
	GLuint ReadImage(std::string path);
};

