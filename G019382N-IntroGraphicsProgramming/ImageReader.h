#pragma once
#include <iostream>

struct Image;

class ImageReader
{
public:
	static Image* ReadImage(std::string path);
};

