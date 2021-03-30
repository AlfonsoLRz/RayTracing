#pragma once

#include "Graphics/Core/Image.h"

/**
*	@file UnsignedImage.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 08/04/2019
*/

/**
*	@brief Image wrapper for ...
*/
class UnsignedImage: public Image<unsigned char>
{
public:
	/**
	*	@brief Constructor of image from a filename from the system.
	*	@param filename Path of image.
	*/
	UnsignedImage(const std::string& filename);

	/**
	*	@brief Constructor of already loaded image, so we just acts as a wrapper.
	*	@param image Array of image bits.
	*	@param width Image width.
	*	@param height Image height.
	*	@param depth Number of channels.
	*/
	UnsignedImage(unsigned char* image, const uint16_t width, const uint16_t height, const uint8_t depth);

	/**
	*	@brief Destructor.
	*/
	~UnsignedImage();
};

