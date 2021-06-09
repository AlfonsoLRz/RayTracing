#pragma once

#include "Graphics/Core/Texture.h"
#include "Utilities/Perlin.h"

/**
*	@file NoiseTexture.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 08/06/2021
*/

/**
*	@brief Texture for Perlin noise function.
*/
class NoiseTexture: public Texture
{
protected:
	float	_frequency;			//!<
	Perlin	_perlinNoise;		//!< Noise function

public:
	/**
	*	@brief Default constructor. 
	*/
	NoiseTexture(float frequency = 1.0f);
	
	/**
	*	@return Color for texture when using texels (u, v).
	*/
	virtual vec3 getColor(const vec2& uv, const vec3& point);
};

