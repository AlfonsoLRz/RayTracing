#include "stdafx.h"
#include "ImageTexture.h"

ImageTexture::ImageTexture(const std::string& filename)
{
	unsigned error = lodepng::decode(_data, _width, _height, filename.c_str());

	if (error)
	{
		std::cout << "The image " << filename << " couldn't be loaded by lodepng" << std::endl;

		_width = _height = _depth = 0;
	}
	else
	{
		_depth = 4;
	}

	//this->flipImageVertically(_image, _width, _height, _depth);				// By default it's flipped
}

ImageTexture::~ImageTexture()
{
}

vec3 ImageTexture::getColor(const vec2& uv, const vec3& point)
{
	if (!_depth) return vec3(.0f, 1.0f, 1.0f);

	int s = static_cast<int>(glm::clamp(uv.x, .0f, 1.0f) * (_width - 1));
	int t = static_cast<int>((1.0f - glm::clamp(uv.y, .0f, 1.0f)) * (_height - 1));
	unsigned baseIndex = t * _width * _depth + s * _depth;

	auto color = vec3(_data[baseIndex + 0], _data[baseIndex + 1], _data[baseIndex + 2]);

	return color / 255.0f;
}
