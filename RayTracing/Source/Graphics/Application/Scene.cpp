#include "stdafx.h"
#include "Scene.h"

#include "Graphics/Core/OpenGLUtilities.h"
#include "Graphics/Core/ShaderList.h"

/// [Public methods]

Scene::Scene():
	_cameraManager(std::unique_ptr<CameraManager>(new CameraManager())), _sceneGroup(nullptr)
{
	_hittableList.reset(new HittableList);
}

Scene::~Scene()
{
	delete _sceneGroup;
}

void Scene::load()
{
	this->loadCameras();
	this->loadLights();
	this->loadModels();

	// Instance BVH from loaded models
	_hittableList->buildBVH();
}

void Scene::modifySize(const uint16_t width, const uint16_t height)
{
	_cameraManager->getActiveCamera()->setRaspect(width, height);
}

void Scene::render(const mat4& mModel, RenderingParameters* rendParams)
{
	Camera* activeCamera = _cameraManager->getActiveCamera();
}

bool Scene::hit(const Ray3D& ray, float tMin, float tMax, Hittable::HitRecord& record)
{
	return _hittableList->hit(ray, tMin, tMax, record);
}

// [Protected methods]

void Scene::loadCameras()
{
	ivec2 canvasSize = Window::getInstance()->getSize();
	Camera* camera = new Camera(canvasSize[0], canvasSize[1]);

	_cameraManager->insertCamera(camera);
}

void Scene::loadLights()
{
}
