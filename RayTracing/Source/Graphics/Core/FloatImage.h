#pragma once

#include "Graphics/Core/Image.h"
#include "Graphics/Core/Texture.h"

/**
*	@file UnsignedImage.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 08/04/2019
*/

/**
*	@brief Image wrapper for ...
*/
class FloatImage: public Image<float>
{
protected:
	GLuint		_ssboID;		//!<
	Texture*	_texture;		//!<

protected:

public:
	/**
	*	@brief Constructor of already loaded image, so we just acts as a wrapper.
	*	@param width Image width.
	*	@param height Image height.
	*	@param depth Number of channels.
	*/
	FloatImage(const uint16_t width, const uint16_t height, const uint8_t depth);

	/**
	*	@brief Destructor.
	*/
	~FloatImage();

	/**
	*	@brief
	*/
	void updateRenderingBuffers();

	/**
	*	@brief  
	*/
	virtual void updateSize(const unsigned width, const unsigned height);

	// ------- Getter --------

	/**
	*	@return Texture with pixel values of float image. 
	*/
	Texture* getTexture() { return _texture; }
};

