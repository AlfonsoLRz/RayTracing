#include "stdafx.h"
#include "FloatImage.h"

FloatImage::FloatImage(const uint16_t width, const uint16_t height, const uint8_t depth) : Image(width, height, depth), _texture(nullptr), _ssboID(0)
{
	_image = std::vector<float>(width * height * depth);
	_texture = new OpenGLTexture(_image.data(), width, height, true, GL_CLAMP, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	_ssboID = ComputeShader::setReadBuffer(_image.data(), _image.size(), GL_DYNAMIC_DRAW);
}

FloatImage::~FloatImage()
{
	delete _texture;
	glDeleteBuffers(1, &_ssboID);
}

void FloatImage::updateRenderingBuffers()
{
	// Update texture
	const GLuint textureID = _texture->getIdentifier();

	{
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_FLOAT, _image.data());
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	// Update SSBO
	ComputeShader::updateReadBuffer(_ssboID, _image.data(), _image.size(), GL_DYNAMIC_DRAW);
}

void FloatImage::updateSize(const unsigned width, const unsigned height)
{
	Image::updateSize(width, height);
	
	this->updateRenderingBuffers();
}
