#include "stdafx.h"
#include "GeometricScene.h"

#include "Graphics/Core/Sphere.h"

// [Protected methods]

void GeometricScene::loadModels()
{
	Material* ground = new Material(vec3(.8f, .8f, .0f));
	ground->setMaterialType(MaterialType::LAMBERTIAN);

	Material* sphereCenter = new Material(vec3(.7, 0.3, 0.3f));
	sphereCenter->setMaterialType(MaterialType::LAMBERTIAN);

	Material* sphereLeft = new Material(vec3(.8f));
	sphereLeft->setMaterialType(MaterialType::METAL);

	Material* sphereRight = new Material(vec3(.8f, .6f, .2f));
	sphereRight->setMaterialType(MaterialType::METAL);

	this->addObject(std::make_shared<Sphere>(vec3(.0f, -100.5f, -1.0f), 100.0f, std::shared_ptr<Material>(ground)));
	this->addObject(std::make_shared<Sphere>(vec3(.0f, .0f, -1.0f), 0.5f, std::shared_ptr<Material>(sphereCenter)));
	this->addObject(std::make_shared<Sphere>(vec3(-1.0f, .0f, -1.0f), 0.5f, std::shared_ptr<Material>(sphereLeft)));
	this->addObject(std::make_shared<Sphere>(vec3(1.0f, .0f, -1.0f), 0.5f, std::shared_ptr<Material>(sphereRight)));
}
