#include "stdafx.h"
#include "Scene.h"

#include "Graphics/Core/OpenGLUtilities.h"
#include "Graphics/Core/ShaderList.h"

/// [Public methods]

Scene::Scene():
	_cameraManager(std::unique_ptr<CameraManager>(new CameraManager())), _sceneGroup(nullptr)
{
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
	_bvh = std::make_unique<BVH>(BVH(_hittableObjects, .0f, 1.0f));
}

void Scene::modifySize(const uint16_t width, const uint16_t height)
{
	_cameraManager->getActiveCamera()->setRaspect(width, height);
}

void Scene::render(const mat4& mModel, RenderingParameters* rendParams)
{
	Camera* activeCamera = _cameraManager->getActiveCamera();
}

bool Scene::getBoundingBox(float time0, float time1, AABB& aabb)
{
	if (_hittableObjects.empty()) return false;

	AABB tempAABB;

	for (std::shared_ptr<Hittable> object : _hittableObjects)
	{
		if (!object->getBoundingBox(time0, time1, tempAABB)) return false;
		aabb.update(tempAABB);
	}

	return true;
}

bool Scene::hit(const Ray3D& ray, float tMin, float tMax, Hittable::HitRecord& record)
{
	Hittable::HitRecord tempRecord;
	bool hitAnything = _bvh->hit(ray, tMin, tMax, record);

	return hitAnything;
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
