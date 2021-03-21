#pragma once

#include "stdafx.h"

/**
*	@file RenderingParameters.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 01/02/2021
*/

/**
*	@brief Wraps the rendering conditions of the application.
*/
struct RenderingParameters
{
public:
	// App
	ivec2							_viewportSize;							//!< Viewport size (!= window)

	// Background
	vec3							_backgroundColor;						//!< Clear color

	// Camera
	bool							_lockCamera;							//!< Disable camera movement (but zoom)

	// Screenshot
	char							_screenshotFilenameBuffer[32];			//!< Path of screenshot
	float							_screenshotMultiplier;					//!< Multiplier of current size of GLFW window
	std::string						_screenshotName;						//!< Name of screenshot (folder is always the same)

public:
	/**
	*	@brief Default constructor.
	*/
	RenderingParameters() :
		_viewportSize(1.0f, 1.0f),

		_backgroundColor(0.4f, 0.4f, 0.4f),

		_lockCamera(false),


		_screenshotFilenameBuffer("Screenshot.png"),
		_screenshotMultiplier(3.0f)
	{
	}
};

