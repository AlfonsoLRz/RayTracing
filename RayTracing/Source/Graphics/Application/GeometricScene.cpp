#include "stdafx.h"
#include "GeometricScene.h"

#include "Graphics/Core/Box.h"
#include "Graphics/Core/ConstantMedium.h"
#include "Graphics/Core/DiffuseLightMaterial.h"
#include "Graphics/Core/ImageTexture.h"
#include "Graphics/Core/MovingSphere.h"
#include "Graphics/Core/NoiseTexture.h"
#include "Graphics/Core/Rectangle.h"
#include "Graphics/Core/Sphere.h"
#include "Graphics/Core/TransformedHittable.h"

// [Public methods]

GeometricScene::GeometricScene() :
	_sceneType(PROCEDURAL_WEEK)
{
}

// [Protected methods]

void GeometricScene::generateCornellBoxScene()
{
	std::shared_ptr<Material> red = std::make_shared<Material>(Material(vec3(.65f, .05f, .05f)));
	red->setMaterialType(MaterialType::LAMBERTIAN);
	std::shared_ptr<Material> white = std::make_shared<Material>(Material(vec3(.73f)));
	white->setMaterialType(MaterialType::LAMBERTIAN);	
	std::shared_ptr<Material> green = std::make_shared<Material>(Material(vec3(.12f, .45f, .15f)));
	green->setMaterialType(MaterialType::LAMBERTIAN);
	std::shared_ptr<Material> light = std::make_shared<Material>(Material(vec3(.0f)));
	light->setEmissionTexture(vec3(7.0f))->setMaterialType(MaterialType::DIFFUSE_LIGHT);

	_hittableList->addObject(std::make_shared<RectangleYZ>(.0f, 555.0f, .0f, 555.0f, 555.0f, std::shared_ptr<Material>(green)));
	_hittableList->addObject(std::make_shared<RectangleYZ>(.0f, 555.0f, .0f, 555.0f, .0f, std::shared_ptr<Material>(red)));
	_hittableList->addObject(std::make_shared<RectangleXY>(.0f, 555.0f, .0f, 555.0f, 555.0f, std::shared_ptr<Material>(white)));
	_hittableList->addObject(std::make_shared<RectangleXZ>(.0f, 555.0f, .0f, 555.0f, .0f, std::shared_ptr<Material>(white)));
	_hittableList->addObject(std::make_shared<RectangleXZ>(.0f, 555.0f, .0f, 555.0f, 555.0f, std::shared_ptr<Material>(white)));
	_hittableList->addObject(std::make_shared<RectangleXZ>(113.0f, 443.0f, 127.0f, 432.0f, 554.0f, std::shared_ptr<Material>(light)));

	std::shared_ptr<Hittable> leftBox = std::make_shared<Box>(vec3(.0f), vec3(165.0f, 330.0f, 165.0f), white);
	leftBox = std::make_shared<RotatedYHittable>(leftBox, 15.0f);
	leftBox = std::make_shared<TranslatedHittable>(leftBox, vec3(265.0f, .0f, 295.0f));
	_hittableList->addObject(std::make_shared<ConstantMedium>(leftBox, vec3(.0f), .01f));

	std::shared_ptr<Hittable> rightBox = std::make_shared<Box>(vec3(.0f), vec3(165.0f), white);
	rightBox = std::make_shared<RotatedYHittable>(rightBox, -18.0f);
	rightBox = std::make_shared<TranslatedHittable>(rightBox, vec3(130.0f, .0f, 65.0f));
	_hittableList->addObject(std::make_shared<ConstantMedium>(rightBox, vec3(1.0f), .01f));
}

void GeometricScene::generateEmissionScene()
{
	Material* ground = (new Material(std::make_shared<NoiseTexture>(NoiseTexture(5.0f, 7))))->setMaterialType(MaterialType::LAMBERTIAN);
	_hittableList->addObject(std::make_shared<Sphere>(vec3(.0f, -1000.0f, .0f), 1000.0f, std::shared_ptr<Material>(ground)));

	Material* sphere = (new Material(vec3(.4f, .2f, .1f)))->setMaterialType(MaterialType::LAMBERTIAN);
	_hittableList->addObject(std::make_shared<Sphere>(vec3(.0f, 2.0f, .0f), 2.0f, std::shared_ptr<Material>(ground)));

	Material* diffuseLight = (new Material(vec3(.0f)))->setEmissionTexture(vec3(1.5f))->setMaterialType(MaterialType::DIFFUSE_LIGHT);
	_hittableList->addObject(std::make_shared<RectangleXY>(3.0f, 5.0f, 1.0f, 3.0f, -2.0f, std::shared_ptr<Material>(diffuseLight)));
	_hittableList->addObject(std::make_shared<Sphere>(vec3(.0f, 7.0f, .0f), 2.0f, std::shared_ptr<Material>(diffuseLight)));
}

void GeometricScene::generateProceduralSceneWeekend()
{
	float matProbs[] = { .8f, .95f, 1.0f };
	
	Material* ground = (new Material(std::make_shared<CheckerTexture>(vec3(1.0f), vec3(.0f))))->setMaterialType(MaterialType::LAMBERTIAN);
	_hittableList->addObject(std::make_shared<Sphere>(vec3(.0f, -1000.0f, .0f), 1000.0f, std::shared_ptr<Material>(ground)));

	Material* sphere1 = (new Material(vec3(.0f)))->setMaterialType(MaterialType::DIELECTRIC)->setRefractionIndex(1.5f);
	_hittableList->addObject(std::make_shared<Sphere>(vec3(.0f, 1.0f, .0f), 1.0f, std::shared_ptr<Material>(sphere1)));

	Material* sphere2 = (new Material(vec3(.4f, .2f, .1f)))->setMaterialType(MaterialType::LAMBERTIAN);
	_hittableList->addObject(std::make_shared<Sphere>(vec3(-4.0f, 1.0f, .0f), 1.0f, std::shared_ptr<Material>(sphere2)));

	Material* sphere3 = (new Material(std::make_shared<ImageTexture>(ImageTexture("Assets/Images/Checker/GGGJ.png"))))->setMaterialType(MaterialType::METAL)->setReflectionFuzz(.0f);
	_hittableList->addObject(std::make_shared<Sphere>(vec3(4.0f, 1.0f, .0f), 1.0f, std::shared_ptr<Material>(sphere3)));

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
					_hittableList->addObject(std::make_shared<MovingSphere>(center, center2, .0f, 1.0f, .2f, std::shared_ptr<Material>(material)));
				}
				else if (matProb < matProbs[1])
				{
					material = (new Material(RandomUtilities::getUniformRandomColor(.5f, 1.0f)))->setMaterialType(MaterialType::METAL)
								->setReflectionFuzz(RandomUtilities::getUniformRandom(.0f, .5f));
					_hittableList->addObject(std::make_shared<Sphere>(center, .2f, std::shared_ptr<Material>(material)));
				}
				else
				{
					material = (new Material(vec3(.0f)))->setMaterialType(MaterialType::DIELECTRIC)->setRefractionIndex(1.5f);
					_hittableList->addObject(std::make_shared<Sphere>(center, .2f, std::shared_ptr<Material>(material)));
				}
			}
		}
	}
}

void GeometricScene::generateProceduralSceneWeek()
{
	std::shared_ptr<HittableList> groundBoxes = std::shared_ptr<HittableList>(new HittableList);	
	Material* groundMaterial = (new Material(vec3(.48, .83f, .53f)))->setMaterialType(MaterialType::LAMBERTIAN);
	const unsigned tileSize = 20;

	for (int x = 0; x < tileSize; ++x)
	{
		for (int z = 0; z < tileSize; ++z)
		{
			float w = 100.0f;
			const float x0 = -1000.0f + x * w;
			const float z0 = -1000.0f + z * w;
			const float y0 = .0f;
			const float x1 = x0 + w;
			const float z1 = z0 + w;
			const float y1 = y0 + RandomUtilities::getUniformRandom(1.0f, 101.0f);

			groundBoxes->addObject(std::make_shared<Box>(vec3(x0, y0, z0), vec3(x1, y1, z1), std::shared_ptr<Material>(groundMaterial)));
		}
	}

	_hittableList->addObject(groundBoxes);
	groundBoxes->buildBVH();

	// Spheres
	std::shared_ptr<Material> light = std::make_shared<Material>(Material(vec3(.0f)));
	light->setEmissionTexture(vec3(7.0f))->setMaterialType(MaterialType::DIFFUSE_LIGHT);
	_hittableList->addObject(std::make_shared<RectangleXZ>(123.0f, 423.0f, 147.0f, 412.0f, 554.0f, std::shared_ptr<Material>(light)));

	vec3 center0(400.0f, 400.0f, 200.0f), center1(center0 + vec3(30.0f, .0f, .0f));
	Material* movingSphereMaterial = (new Material(vec3(0.7f, .3f, .1f)))->setMaterialType(MaterialType::LAMBERTIAN);
	_hittableList->addObject(std::make_shared<MovingSphere>(center0, center1, .0f, 1.0f, 50.0f, std::shared_ptr<Material>(movingSphereMaterial)));

	Material* dielectricSphere = (new Material)->setRefractionIndex(1.5f)->setMaterialType(MaterialType::DIELECTRIC);
	Material* metallicSphere = (new Material(vec3(.8f, .8f, .9f)))->setReflectionFuzz(1.0f)->setMaterialType(MaterialType::METAL);
	_hittableList->addObject(std::make_shared<Sphere>(vec3(260.0f, 150.0f, 45.0f), 50.0f, std::shared_ptr<Material>(dielectricSphere)));
	_hittableList->addObject(std::make_shared<Sphere>(vec3(0.0f, 150.0f, 145.0f), 50.0f, std::shared_ptr<Material>(metallicSphere)));

	std::shared_ptr<Sphere> volumeBoundary = std::make_shared<Sphere>(vec3(360.0f, 150.0f, 145.0f), 70.0f, std::shared_ptr<Material>(dielectricSphere));
	_hittableList->addObject(volumeBoundary);
	_hittableList->addObject(std::make_shared<ConstantMedium>(volumeBoundary, vec3(0.2f, 0.4f, 0.9f), 0.2f));
	volumeBoundary = std::make_shared<Sphere>(vec3(.0f), 5000.0f, std::shared_ptr<Material>(dielectricSphere));
	_hittableList->addObject(make_shared<ConstantMedium>(volumeBoundary, vec3(1.0f, 1.0f, 1.0f), .0001f));

	Material* imageMaterial = (new Material(std::make_shared<ImageTexture>(ImageTexture("Assets/Images/Checker/GGGJ.png"))))->setMaterialType(MaterialType::LAMBERTIAN);
	_hittableList->addObject(std::make_shared<Sphere>(vec3(400.0f, 200.0f, 400.0f), 100.0f, std::shared_ptr<Material>(imageMaterial)));
	
	Material* perlinNoise = (new Material(std::make_shared<NoiseTexture>(NoiseTexture(.1f))))->setMaterialType(MaterialType::LAMBERTIAN);
	_hittableList->addObject(std::make_shared<Sphere>(vec3(220.0f, 280.0f, 300.0f), 80.0f, std::shared_ptr<Material>(perlinNoise)));

	std::shared_ptr<HittableList> boxSpheres = std::shared_ptr<HittableList>(new HittableList);
	Material* whiteMaterial = (new Material(vec3(.73f)))->setMaterialType(MaterialType::LAMBERTIAN);
	const unsigned numberSpheres = 1000;
	
	for (int j = 0; j < numberSpheres; j++) 
	{
		boxSpheres->addObject(std::make_shared<Sphere>(RandomUtilities::getUniformRandomColor() * 165.0f, 10.0f, std::shared_ptr<Material>(whiteMaterial)));
	}

	_hittableList->addObject(std::make_shared<TranslatedHittable>(std::make_shared<RotatedYHittable>(boxSpheres, 15.0f), vec3(-100.0f, 270.0f, 395.0f)));
	boxSpheres->buildBVH();
}

void GeometricScene::loadCameras()
{
	Camera* camera;
	vec3 eye, lookAt;
	ivec2 canvasSize = Window::getInstance()->getSize();;
	
	switch (_sceneType)
	{
	case CORNELL_BOX:
		eye = vec3(278.0f, 280.0f, -800.0f), lookAt = vec3(278.0f, 278.0f, 0.0f);
		camera = (new Camera(canvasSize[0], canvasSize[1]))->setPosition(eye)->setLookAt(lookAt)->setFovY(40.0f)->setFocusDistance(10.0f)
														   ->setTimeFrame(vec2(.0f, 1.0f))->buildDescription();

		_cameraManager->insertCamera(camera);

		break;

	case EMISSION:
		eye = vec3(26.0f, 3.0f, 6.0f), lookAt = vec3(.0f, 2.0f, 0.0f);
		camera = (new Camera(canvasSize[0], canvasSize[1]))->setPosition(eye)->setLookAt(lookAt)->setFovY(20.0f)->setTimeFrame(vec2(.0f, 1.0f))->buildDescription();

		_cameraManager->insertCamera(camera);

		break;
		
	case PROCEDURAL_WEEKEND:
		eye = vec3(13.0f, 2.0f, 3.0f), lookAt = vec3(.0f, .0f, 0.0f);
		camera = (new Camera(canvasSize[0], canvasSize[1]))->setPosition(eye)->setLookAt(lookAt)->setFovY(20.0f)
														   ->setAperture(.1f)->setFocusDistance(10.0f)->setTimeFrame(vec2(.0f, 1.0f))->buildDescription();

		_cameraManager->insertCamera(camera);

		break;
		
	case PROCEDURAL_WEEK:
		eye = vec3(478.0f, 278.0f, -600.0f), lookAt = vec3(278.0f, 278.0f, 0.0f);
		camera = (new Camera(canvasSize[0], canvasSize[1]))->setPosition(eye)->setLookAt(lookAt)->setFovY(40.0f)->setTimeFrame(vec2(.0f, 1.0f))->buildDescription();

		_cameraManager->insertCamera(camera);
		
		break;
		
	default:
		eye = vec3(3.0f, 3.0f, 2.0f), lookAt = vec3(.0f, .0f, -1.0f);
		camera = (new Camera(canvasSize[0], canvasSize[1]))->setPosition(eye)->setLookAt(lookAt)->setFovY(20.0f)
														   ->setAperture(1.0f)->setFocusDistance(glm::length(eye - lookAt))->buildDescription();

		_cameraManager->insertCamera(camera);
	}
}

void GeometricScene::loadModels()
{
	switch (_sceneType)
	{
	case CORNELL_BOX:
		this->generateCornellBoxScene();

		break;

	case EMISSION:
		this->generateEmissionScene();

		break;

	case PROCEDURAL_WEEKEND:
		this->generateProceduralSceneWeekend();

		break;

	case PROCEDURAL_WEEK:
		this->generateProceduralSceneWeek();

		break;
		
	default:
		Material* ground = new Material(vec3(.8f, .8f, .0f));
		ground->setMaterialType(MaterialType::LAMBERTIAN);

		Material* sphereCenter = new Material(vec3(.1f, .2f, .5f));
		sphereCenter->setMaterialType(MaterialType::LAMBERTIAN);

		Material* sphereLeft = new Material(vec3(.8f));
		sphereLeft->setMaterialType(MaterialType::DIELECTRIC)->setReflectionFuzz(.3f);

		Material* sphereRight = new Material(vec3(.8f, .6f, .2f));
		sphereRight->setMaterialType(MaterialType::METAL)->setReflectionFuzz(1.0f);

		_hittableList->addObject(std::make_shared<Sphere>(vec3(.0f, -100.5f, -1.0f), 100.0f, std::shared_ptr<Material>(ground)));
		_hittableList->addObject(std::make_shared<Sphere>(vec3(.0f, .0f, -1.0f), 0.5f, std::shared_ptr<Material>(sphereCenter)));
		_hittableList->addObject(std::make_shared<Sphere>(vec3(-1.0f, .0f, -1.0f), 0.5f, std::shared_ptr<Material>(sphereLeft)));
		_hittableList->addObject(std::make_shared<Sphere>(vec3(1.0f, .0f, -1.0f), 0.5f, std::shared_ptr<Material>(sphereRight)));

		break;
	}
}
