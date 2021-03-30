#include "stdafx.h"
#include "UnsignedImage.h"

/// [Public methods]

UnsignedImage::UnsignedImage(const std::string& filename) : Image(0, 0, 4)
{
	unsigned error = lodepng::decode(_image, _width, _height, filename.c_str());

	if (error)
	{
		std::cout << "The image " << filename << " couldn't be loaded by lodepng" << std::endl;

		_width = _height = _depth = 0;
	}

	this->flipImageVertically(_image, _width, _height, _depth);				// By default it's flipped
}

UnsignedImage::UnsignedImage(unsigned char* image, const uint16_t width, const uint16_t height, const uint8_t depth) :
	Image(_width, _height, _depth)
{
	if (image)
	{
		const int size = width * height * depth;
		_image = std::vector<unsigned char>(image, image + size);
	}
	else
	{
		std::cout << "Empty image!" << std::endl;

		_width = _height = _depth = 0;
	}
}

UnsignedImage::~UnsignedImage()
{
}