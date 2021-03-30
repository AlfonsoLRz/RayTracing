#pragma once

#include "stdafx.h"

/**
*	@file GraphicsAppEnumerations.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 07/12/2019
*/

/**
*	@brief Enumerations for any component of this application.
*/
struct CGApplicationEnumerations
{
	// Drawable scenes
	enum SceneNames : uint8_t
	{
		TEST_SCENE
	};

	/**
	*	@return Number of drawable scenes.
	*/
	const static GLsizei numAvailableScenes() { return TEST_SCENE + 1; }


	// Application prebuilt materials
	enum MaterialNames : uint16_t
	{
		MATERIAL_CAD_WHITE
	};

	// Application prebuilt textures
	enum TextureNames : uint16_t
	{
		TEXTURE_BLACK,
		TEXTURE_BLUE,
		TEXTURE_GRAY_64,
		TEXTURE_GRAY_127,
		TEXTURE_GRAY_192,
		TEXTURE_GREEN,
		TEXTURE_RED,
		TEXTURE_WHITE,
		TEXTURE_YELLOW
	};

	/**
	*	@return Number of built-in materials.
	*/
	const static GLsizei numAvailableMaterials() { return MATERIAL_CAD_WHITE + 1; }

	/**
	*	@return Number of built-in textures.
	*/
	const static GLsizei numAvailableTextures() { return TEXTURE_YELLOW + 1; }
};