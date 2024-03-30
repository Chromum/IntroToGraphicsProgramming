#include "ImageReader.h"
#include <fstream>
#include <vector>
#include "Image.h"

Image* ImageReader::ReadImage(std::string path)
{
	unsigned int width;
	unsigned int height;
	std::vector<Color> colors;

	std::fstream stream;
	stream.open(path, std::ios::in | std::ios::binary);

	if (!stream.is_open())
		std::cout << "File could not be open" << std::endl;

	const int fileHeaderSize = 14;
	const int infoHeaderSize = 40;

	unsigned char fileHeader[fileHeaderSize];
	stream.read(reinterpret_cast<char*>(fileHeader), fileHeaderSize);

	unsigned char infoHeader[infoHeaderSize];
	stream.read(reinterpret_cast<char*>(infoHeader), infoHeaderSize);

	int fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);

	width = infoHeader[4] + (infoHeader[5] << 8) + (infoHeader[6] << 16) + (infoHeader[7] << 24);
	height = infoHeader[8] + (infoHeader[9] << 8) + (infoHeader[10] << 16) + (infoHeader[11] << 24);

	colors.resize(width*height);

	const int paddingAmount = ((4 - (width * 3) % 4) % 4);

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			unsigned char color[3];
			stream.read(reinterpret_cast<char*>(color), 3);


			colors[x * width + y].r = static_cast<float>(color[2] / 255.0f);
			colors[x * width + y].g = static_cast<float>(color[1] / 255.0f);
			colors[x * width + y].b = static_cast<float>(color[0] / 255.0f);
		}
		stream.ignore(paddingAmount);
	}

	stream.close();





	std::cout << width << ":" << height << std::endl;
	Image* imagetoReturn = new Image(colors, width, height);
	return imagetoReturn;
}
