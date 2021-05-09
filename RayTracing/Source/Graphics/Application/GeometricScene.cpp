#include "stdafx.h"
#include "GeometricScene.h"

#include "Graphics/Core/MovingSphere.h"
#include "Graphics/Core/Sphere.h"

// [Protected methods]

void GeometricScene::generateProceduralScene()
{
	float matProbs[] = { .8f, .95f, 1.0f };
	
	Material* ground = (new Material(vec3(.5f)))->setMaterialType(MaterialType::LAMBERTIAN);
	this->addObject(std::make_shared<Sphere>(vec3(.0f, -1000.0f, .0f), 1000.0f, std::shared_ptr<Material>(ground)));

	Material* sphere1 = (new Material(vec3(.0f)))->setMaterialType(MaterialType::DIELECTRIC)->setRefractionIndex(1.5f);
	this->addObject(std::make_shared<Sphere>(vec3(.0f, 1.0f, .0f), 1.0f, std::shared_ptr<Material>(sphere1)));

	Material* sphere2 = (new Material(vec3(.4f, .2f, .1f)))->setMaterialType(MaterialType::LAMBERTIAN);
	this->addObject(std::make_shared<Sphere>(vec3(-4.0f, 1.0f, .0f), 1.0f, std::shared_ptr<Material>(sphere2)));

	Material* sphere3 = (new Material(vec3(.7f, .6f, .5f)))->setMaterialType(MaterialType::METAL)->setReflectionFuzz(.0f);
	this->addObject(std::make_shared<Sphere>(vec3(4.0f, 1.0f, .0f), 1.0f, std::shared_ptr<Material>(sphere3)));

	for (int a = -11; a < 11; ++a)
	{
		for (int b = -11; b < 11; ++b)
		{
			float matProb = RandomUtilities::getUniformRandom();
			vec3 center(a + .9f * RandomUtilities::getUniformRandom(), .2f, b + .9f * RandomUtilities::getUniformRandom());

			if (glm::length(center - vec3(4.0f, .2f, .0f)) > .9f)
			{
				Material* material;
				vec3 center2 = center + vec3(.0f, RandomUtilities::getUniformRandom(.0f, .5f), .0f);

				if (matProb < matProbs[0])
				{
					material = (new Material(RandomUtilities::getUniformRandomColor()))->setMaterialType(MaterialType::LAMBERTIAN);
					this->addObject(std::make_shared<MovingSphere>(center, center2, .0f, 1.0f, .2f, std::shared_ptr<Material>(material)));
				}
				else if (matProb < matProbs[1])
				{
					material = (new Material(RandomUtilities::getUniformRandomColor(.5f, 1.0f)))->setMaterialType(MaterialType::METAL)
								->setReflectionFuzz(RandomUtilities::getUniformRandom(.0f, .5f));
					this->addObject(std::make_shared<Sphere>(center, .2f, std::shared_ptr<Material>(material)));
				}
				else
				{
					material = (new Material(vec3(.0f)))->setMaterialType(MaterialType::DIELECTRIC)->setRefractionIndex(1.5f);
					this->addObject(std::make_shared<Sphere>(center, .2f, std::shared_ptr<Material>(material)));
				}
			}
		}
	}
}

void GeometricScene::loadCameras()
{
#if PROCEDURAL_SCENE
	const vec3 eye = vec3(13.0f, 2.0f, 3.0f), lookAt = vec3(.0f, .0f, 0.0f);
	ivec2 canvasSize = Window::getInstance()->getSize();
	Camera* camera = (new Camera(canvasSize[0], canvasSize[1]))->setPosition(eye)->setLookAt(lookAt)->setFovY(20.0f)
		->setAperture(.1f)->setFocusDistance(10.0f)->setTimeFrame(vec2(.0f, 1.0f))->buildDescription();

	_cameraManager->insertCamera(camera);
	
#else
	const vec3 eye = vec3(3.0f, 3.0f, 2.0f), lookAt = vec3(.0f, .0f, -1.0f);
	ivec2 canvasSize = Window::getInstance()->getSize();
	Camera* camera = (new Camera(canvasSize[0], canvasSize[1]))->setPosition(eye)->setLookAt(lookAt)->setFovY(20.0f)
					->setAperture(1.0f)->setFocusDistance(glm::length(eye - lookAt))->buildDescription();

	_cameraManager->insertCamera(camera);
#endif
}

void GeometricScene::loadModels()
{
#if PROCEDURAL_SCENE
	this->generateProceduralScene();
#else
	Material* ground = new Material(vec3(.8f, .8f, .0f));
	ground->setMaterialType(MaterialType::LAMBERTIAN);

	Material* sphereCenter = new Material(vec3(.1f, .2f, .5f));
	sphereCenter->setMaterialType(MaterialType::LAMBERTIAN);

	Material* sphereLeft = new Material(vec3(.8f));
	sphereLeft->setMaterialType(MaterialType::DIELECTRIC)->setReflectionFuzz(.3f);

	Material* sphereRight = new Material(vec3(.8f, .6f, .2f));
	sphereRight->setMaterialType(MaterialType::METAL)->setReflectionFuzz(1.0f);

	this->addObject(std::make_shared<Sphere>(vec3(.0f, -100.5f, -1.0f), 100.0f, std::shared_ptr<Material>(ground)));
	this->addObject(std::make_shared<Sphere>(vec3(.0f, .0f, -1.0f), 0.5f, std::shared_ptr<Material>(sphereCenter)));
	this->addObject(std::make_shared<Sphere>(vec3(-1.0f, .0f, -1.0f), 0.5f, std::shared_ptr<Material>(sphereLeft)));
	this->addObject(std::make_shared<Sphere>(vec3(1.0f, .0f, -1.0f), 0.5f, std::shared_ptr<Material>(sphereRight)));
#endif
}
