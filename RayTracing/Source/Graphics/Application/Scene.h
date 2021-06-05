#pragma once

#include "DataStructures/BVH.h"
#include "Graphics/Application/CameraManager.h"
#include "Graphics/Application/MaterialList.h"
#include "Graphics/Application/RenderingParameters.h"
#include "Graphics/Core/Camera.h"
#include "Graphics/Core/Group3D.h"
#include "Graphics/Core/Hittable.h"
#include "Graphics/Core/Model3D.h"
#include "Graphics/Core/ShaderProgram.h"
#include "Interface/Window.h"

/**
*	@file Scene.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
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

	// [Hittable list]
	std::unique_ptr<BVH> _bvh;											//!<
	std::vector<std::shared_ptr<Hittable>> _hittableObjects;			//!< 

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

	// [Object Management]

	/**
	*	@brief  
	*/
	void addObject(std::shared_ptr<Hittable> object) { _hittableObjects.push_back(object); }

	/**
	*	@brief 
	*/
	void clearObjects() { _hittableObjects.clear(); }

	/**
	*	@brief
	*/
	virtual bool getBoundingBox(float time0, float time1, AABB& aabb);

	/**
	*	@brief  
	*/
	virtual bool hit(const Ray3D& ray, float tMin, float tMax, Hittable::HitRecord& record);
};

