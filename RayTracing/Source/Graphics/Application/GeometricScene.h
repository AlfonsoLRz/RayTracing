#pragma once

#include "Graphics/Application/Scene.h"

#define CORNELL_BOX_SCENE true
#define EMISSION_SCENE true
#define PROCEDURAL_SCENE false

/**
*	@file GeometricScene.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 07/12/2019
*/

/**
*	@brief 
*/
class GeometricScene: public Scene
{
protected:
	/**
	*	@brief  
	*/
	void generateCornellBoxScene();
	
	/**
	*	@brief
	*/
	void generateEmissionScene();
	
	/**
	*	@brief 
	*/
	void generateProceduralScene();

	/**
	*	@brief Defines cameras to visualize the scene.
	*/
	virtual void loadCameras();
	
	/**
	*	@brief 
	*/
	virtual void loadModels();
};

