#pragma once

#include "stdafx.h"

/**
*	@file Image.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 08/04/2019
*/

/**
*	@brief Image wrapper for a set of bits with associated information.
*/
template<class T>
class Image
{
protected:
	std::vector<T> _image;							//!< Image pixels
	unsigned _width, _height, _depth;				//!< Image dimensions

public:
	/**
	*	@brief 
	*/
	Image(unsigned width, unsigned height, unsigned depth);

	/**
	*	@brief Destructor.
	*/
	virtual ~Image();

	/**
	*	@return Array of bits from image.
	*/
	T* bits() { return _image.data(); }

	/**
	*	@brief Flips the image so that bottom side turns into the upper side.
	*	@param image Array of image bits.
	*	@param width Image width.
	*	@param height Image height.
	*	@param depth Number of channels.
	*/
	void flipImageVertically();

	/**
	*	@brief  
	*/
	virtual void updateSize(const unsigned width, const unsigned height);

	// Getters

	/**
	*	@return Number of channels of image.
	*/
	int getDepth() const { return _depth; }

	/**
	*	@return Height of image.
	*/
	int getHeight() const { return _height; }

	/**
	*	@return Width of image.
	*/
	int getWidth() const { return _width; }

	// ----------- Static methods ------------

	/**
	*	@brief Flips the image so that bottom side turns into the upper side.
	*	@param image Array of image bits.
	*	@param width Image width.
	*	@param height Image height.
	*	@param depth Number of channels.
	*/
	static void flipImageVertically(std::vector<T>& image, const uint16_t width, const uint16_t height, const uint8_t depth);
};

template<class T>
inline Image<T>::Image(unsigned width, unsigned height, unsigned depth) :
	_width(width), _height(height), _depth(depth)
{
}

template<class T>
inline Image<T>::~Image()
{
}

template<class T>
inline void Image<T>::flipImageVertically()
{
	Image::flipImageVertically(_image, _width, _height, _depth);
}

template<class T>
inline void Image<T>::updateSize(const unsigned width, const unsigned height)
{
	_width = width; _height = height;
	_image.resize(_width * _height * _depth);
}

template<class T>
inline void Image<T>::flipImageVertically(std::vector<T>& image, const uint16_t width, const uint16_t height, const uint8_t depth)
{
	int rowSize = width * depth;
	T* bits = image.data();
	T* tempBuffer = new unsigned char[rowSize];

	for (int i = 0; i < (height / 2); ++i)
	{
		T* source = bits + i * rowSize;
		T* target = bits + (height - i - 1) * rowSize;

		memcpy(tempBuffer, source, rowSize);					// Swap with help of temporary buffer
		memcpy(source, target, rowSize);
		memcpy(target, tempBuffer, rowSize);
	}

	delete[] tempBuffer;
}
