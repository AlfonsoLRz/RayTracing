#pragma once

#include "Graphics/Application/Scene.h"

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
	enum SceneType
	{
		CORNELL_BOX, EMISSION, PROCEDURAL_WEEKEND, PROCEDURAL_WEEK
	};

protected:
	SceneType	_sceneType;

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
	void generateProceduralSceneWeekend();

	/**
	*	@brief
	*/
	void generateProceduralSceneWeek();

	/**
	*	@brief Defines cameras to visualize the scene.
	*/
	virtual void loadCameras();
	
	/**
	*	@brief 
	*/
	virtual void loadModels();

public:
	/**
	*	@brief Default constructor. 
	*/
	GeometricScene();
};

