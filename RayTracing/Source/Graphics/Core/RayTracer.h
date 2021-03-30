#pragma once

#include "Graphics/Core/ComputeShader.h"
#include "Graphics/Core/FloatImage.h"
#include "Graphics/Core/OpenGLUtilities.h"
#include "Graphics/Core/RenderingShader.h"
#include "Utilities/Singleton.h"

/**
*	@file FBO.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 07/26/2019
*/

#define DEBUG_MODE

/**
*	@brief Additional framebuffer to perform operations.
*/
class RayTracer : public Singleton<RayTracer>
{
	friend class Singleton<RayTracer>;

protected:
	// [Rendering]
	FloatImage*		_rayTracingImage;	//!<
	VAO*			_quadVAO;			//!< VAO where our new frames are rendered

protected:
	/**
	*	@brief Protected constructor for a Singleton class. 
	*/
	RayTracer();

	/**
	*	 @brief 
	*/
	void drawDebugTexture();

public:
	/**
	*	@brief Destructor. 
	*/
	virtual ~RayTracer();
	
	/**
	*	@brief Renders the new frame of an scene. 
	*/
	void renderFrame();

	/**
	*	@brief  
	*/
	void updateSize(const uint16_t width, const uint16_t height);

	// 
};

