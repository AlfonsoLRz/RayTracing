#pragma once

#include "Graphics/Application/CameraManager.h"
#include "Graphics/Application/MaterialList.h"
#include "Graphics/Application/RenderingParameters.h"
#include "Graphics/Core/Camera.h"
#include "Graphics/Core/Group3D.h"
#include "Graphics/Core/Model3D.h"
#include "Graphics/Core/ShaderProgram.h"
#include "Interface/Window.h"

/**
*	@file Scene.h
*	@authors Alfonso L�pez Ruiz (alr00048@red.ujaen.es)
*	@date 07/12/2019
*/

/**
*	@brief Base class for any drawable scene.
*/
class Scene
{
protected:
	// [General scene]
	std::unique_ptr<CameraManager>		_cameraManager;					//!< Contains the cameras of this scene
	Group3D*							_sceneGroup;					//!< Model wrapper

protected:
	// --------------- Load ----------------

	/**
	*	@brief To be implemented: define cameras to visualize the scene.
	*/
	virtual void loadCameras();

	/**
	*	@brief To be implemented: define lights of the scene.
	*/
	virtual void loadLights();

	/**
	*	@brief To be implemented: define models which take part of the scene.
	*/
	virtual void loadModels() = 0;

public:
	/**
	*	@brief Default constructor. Intializes some generic components.
	*/
	Scene();

	/**
	*	@brief Destructor.
	*/
	~Scene();

	/**
	*	@return Manager of application cameras.
	*/
	CameraManager* getCameraManager()  const { return _cameraManager.get(); }

	/**
	*	@return Group where the scene models are gathered.
	*/
	virtual Group3D* getRenderingGroup() { return _sceneGroup; }

	/**
	*	@brief Loads the elements from the scene: lights, cameras, models, etc.
	*/
	virtual void load();

	/**
	*	@brief Resize event.
	*	@param width New canvas width.
	*	@param height New canvas height.
	*/
	virtual void modifySize(const uint16_t width, const uint16_t height);

	/**
	*	@brief Draws the scene as the rendering parameters specifies.
	*	@param mModel Additional model matrix to be applied over the initial model matrix.
	*	@param rendParams Rendering parameters to be taken into account.
	*/
	virtual void render(const mat4& mModel, RenderingParameters* rendParams);
};
