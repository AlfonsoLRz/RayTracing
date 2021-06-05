#pragma once

#include "Graphics/Core/Texture.h"

/**
*	@file ImageTexture.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 05/06/2021
*/

/**
*	@brief
*/
class ImageTexture: public Texture
{
protected:
	std::vector<unsigned char>	_data;							//!<
	unsigned					_height, _width, _depth;		//!<

public:
	/**
	*	@brief
	*/
	ImageTexture(const std::string& filename);

	/**
	*	@brief Destructor.
	*/
	virtual ~ImageTexture();

	/**
	*	@return Color for texture when using texels (u, v).
	*/
	virtual vec3 getColor(const vec2& uv, const vec3& point);
};

