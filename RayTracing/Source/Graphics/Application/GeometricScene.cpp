#include "stdafx.h"
#include "GeometricScene.h"

#include "Graphics/Core/Sphere.h"

// [Protected methods]

void GeometricScene::loadModels()
{
	this->addObject(std::make_shared<Sphere>(vec3(.0f, .0f, -1.0f), 0.5f));
	this->addObject(std::make_shared<Sphere>(vec3(.0f, -100.5f, -1.0f), 100.0f));
}
