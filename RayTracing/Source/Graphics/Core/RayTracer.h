#pragma once

#include "Geometry/3D/Ray3D.h"
#include "Graphics/Application/Scene.h"
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
#define MAX_DEPTH 40
#define NUM_SAMPLES 50

/**
*	@brief Additional framebuffer to perform operations.
*/
class RayTracer : public Singleton<RayTracer>
{
	friend class Singleton<RayTracer>;

protected:
	const vec3 BACKGROUND_INTERP_COLOR_01 = vec3(1.0f);
	const vec3 BACKGROUND_INTERP_COLOR_02 = vec3(0.5f, 0.7f, 1.0f);

protected:
	// [Rendering]
	FloatImage*		_rayTracingImage;	//!< 
	Scene*			_scene;				//!<
	VAO*			_quadVAO;			//!< VAO where our new frames are rendered

protected:
	/**
	*	@brief Protected constructor for a Singleton class. 
	*/
	RayTracer();

	/**
	*	@brief 
	*/
	void drawDebugTexture();

	/**
	*	@return Default color for image background. 
	*/
	vec3 getBackgroundColor(const Ray3D& ray);

	/**
	*	@brief  
	*/
	vec3 getRayColor(const Ray3D& ray, Scene* scene, int depth);

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
	void updateScene(Scene* scene);

	/**
	*	@brief  
	*/
	void updateSize(const uint16_t width, const uint16_t height);

	// 
};

