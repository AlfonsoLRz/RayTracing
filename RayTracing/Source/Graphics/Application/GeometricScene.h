#pragma once

#include "Graphics/Application/Scene.h"

#define PROCEDURAL_SCENE false
#define EMISSION_SCENE true

/**
*	@file GeometricScene.h
*	@authors Alfonso L�pez Ruiz (alr00048@red.ujaen.es)
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

