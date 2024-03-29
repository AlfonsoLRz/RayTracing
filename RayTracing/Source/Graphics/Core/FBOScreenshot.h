#pragma once

#include "Graphics/Core/FBO.h"
#include "Graphics/Core/UnsignedImage.h"

/**
*	@file FBOScreenshot.h
*	@authors Alfonso L�pez Ruiz (alr00048@red.ujaen.es)
*	@date 07/26/2019
*/

/**
*	@brief Specialized framebuffer to take screenshots of the scene.
*/
class FBOScreenshot: public FBO
{
protected:
	GLuint _multisampledFBO, _colorBufferID;
	GLuint _mColorBufferID, _mDepthBufferID;						//!< Multisampling buffers

protected:
	/**
	*	@brief Writes an image in file system in an isolated thread, so the application doesn't get stuck.
	*	@param pixels Pixels of image to be written.
	*	@param filename Path where the image must be written.
	*	@param width Width of image.
	*	@param height Height of image.
	*/
	void threadedWriteImage(std::vector<GLubyte>* pixels, const std::string& filename, const uint16_t width, const uint16_t height);

public:
	/**
	*	@brief Constructor.
	*	@param width Width of image we want to take.
	*	@param height Height of image we want to take.
	*/
	FBOScreenshot(const uint16_t width, const uint16_t height);

	/**
	*	@brief Destructor.
	*/
	virtual ~FBOScreenshot();

	/**
	*	@brief Binds the framebuffer so it gets active.
	*/
	virtual bool bindFBO();

	/**
	*	@brief ID provided by OpenGL for this framebuffer.
	*/
	virtual GLuint getIdentifier()  const { return _multisampledFBO; }

	/**
	*	@return Rendered screen as an image.
	*/
	UnsignedImage* getImage();

	/**
	*	@brief Modifies the size specified in textures related to framebuffer. To be defined.
	*	@param width New width.
	*	@param height New height.
	*/
	virtual void modifySize(const uint16_t width, const uint16_t height);

	/**
	*	@brief Saves the captured scene in a file.
	*	@param filename Path of file.
	*/
	bool saveImage(const std::string& filename);
};

