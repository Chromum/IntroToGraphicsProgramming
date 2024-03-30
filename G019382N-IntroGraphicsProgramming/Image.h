#pragma once
#include <vector>

struct Color {
	float r, g, b;
	Color() {};
	Color(float r, float g, float b) {
		this->r = r;
		this->b = b;
		this->g = g;
	};
	~Color() {};
};


struct Image {
public:
	Image() {};
	int width;
	int height;
	std::vector<Color> colors;
	Image(std::vector<Color> colors, int width, int height) {
		this->colors = colors;
		this->width = width;
		this->height = height;
	}
};