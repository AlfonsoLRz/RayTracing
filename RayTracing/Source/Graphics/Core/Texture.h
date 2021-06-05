#pragma once

#include "Graphics/Core/ComputeShader.h"
#include "Graphics/Core/UnsignedImage.h"
#include "Graphics/Core/ShaderProgram.h"

/**
*	@file Texture.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 05/06/2021
*/

/**
*	@brief Wraps an image which forms a material.
*/
class Texture
{
public:
	/**
	*	@brief Destructor.
	*/
	virtual ~Texture();

	/**
	*	@return Color for texture when using texels (u, v). 
	*/
	virtual vec3 getColor(const vec2& uv, const vec3& point) = 0;
};

/**
*	@brief Uniform texture.
*/
class SolidColor: public Texture
{
protected:
	vec3 _color;

public:
	/**
	*	@brief
	*/
	SolidColor();

	/**
	*	@brief  
	*/
	SolidColor(const vec3& color);
	
	/**
	*	@brief Destructor.
	*/
	virtual ~SolidColor();

	/**
	*	@return Color for texture when using texels (u, v).
	*/
	virtual vec3 getColor(const vec2& uv, const vec3& point);
};

/**
*	@brief Texture with test pattern.
*/
class CheckerTexture : public Texture
{
protected:
	std::shared_ptr<Texture> _textureOdd, _textureEven;

public:
	/**
	*	@brief
	*/
	CheckerTexture(const vec3& odd, const vec3& even);

	/**
	*	@brief Destructor.
	*/
	virtual ~CheckerTexture();

	/**
	*	@return Color for texture when using texels (u, v).
	*/
	virtual vec3 getColor(const vec2& uv, const vec3& point);
};