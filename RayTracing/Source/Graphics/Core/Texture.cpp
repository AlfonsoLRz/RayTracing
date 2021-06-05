#include "stdafx.h"
#include "Texture.h"

Texture::~Texture()
{

}

// Solid color

SolidColor::SolidColor() : _color(1.0f)
{
}

SolidColor::SolidColor(const vec3& color) : _color(color)
{
}

SolidColor::~SolidColor()
{
}

vec3 SolidColor::getColor(const vec2& uv, const vec3& point)
{
	return _color;
}

// Checker texture

CheckerTexture::CheckerTexture(const vec3& odd, const vec3& even)
{
	_textureOdd.reset(new SolidColor(odd));
	_textureEven.reset(new SolidColor(even));
}

CheckerTexture::~CheckerTexture()
{
}

vec3 CheckerTexture::getColor(const vec2& uv, const vec3& point)
{
	float sine = std::sin(10.0f * point.x) * std::sin(10.0f * point.y) * std::sin(10.0f * point.z);

	return (sine < 0) ? _textureOdd->getColor(uv, point) : _textureEven->getColor(uv, point);
}
