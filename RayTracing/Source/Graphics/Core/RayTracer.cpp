#include "stdafx.h"
#include "RayTracer.h"

#include "Graphics/Core/ShaderList.h"
#include "Graphics/Core/Sphere.h"
#include "Interface/Window.h"
#include "Utilities/RandomUtilities.h"

// [Public methods]

RayTracer::~RayTracer()
{
	delete _rayTracingImage;
}

void RayTracer::renderFrame()
{
	VAO* quadVAO = OpenGLPrimitives::getQuadVAO();
	OpenGLTexture* image = _rayTracingImage->getTexture();

	this->drawDebugTexture();
	_rayTracingImage->updateRenderingBuffers();

	RenderingShader* shader = ShaderList::getInstance()->getRenderingShader(CGEnumerations::REND_TO_QUAD_SHADER);
	shader->use();
	image->applyTexture(shader, 0, "texSampler");
	shader->applyActiveSubroutines();

	quadVAO->drawObject(CGEnumerations::IBO_TRIANGLE_MESH, GL_TRIANGLES, 2 * 4);
}

void RayTracer::updateScene(Scene* scene)
{
	_scene = scene;
}

void RayTracer::updateSize(const uint16_t width, const uint16_t height)
{
	_rayTracingImage->updateSize(width, height);
	_rayTracingImage->updateRenderingBuffers();
}

// [Protected methods]

RayTracer::RayTracer() : _scene(nullptr)
{
	const ivec2 canvasSize = Window::getInstance()->getSize();
	
	_rayTracingImage = new FloatImage(canvasSize.x, canvasSize.y, 4);
	_quadVAO = OpenGLPrimitives::getQuadVAO();
}

void RayTracer::drawDebugTexture()
{
	if (!_scene) return;

	const unsigned width = _rayTracingImage->getWidth(), height = _rayTracingImage->getHeight();
	float* image = _rayTracingImage->bits();
	Ray3D ray (vec3(.0f), vec3(.0f));

	// [Camera]
	Camera* camera =_scene->getCameraManager()->getActiveCamera();

	for (unsigned x = 0; x < width; ++x)
	{
		for (unsigned y = 0; y < height; ++y)
		{
			vec3 color(.0f);

			for (int sampleIdx = 0; sampleIdx < NUM_SAMPLES; ++sampleIdx)
			{
				float u = (x + RandomUtilities::getUniformRandom()) / float(width - 1), v = (y + RandomUtilities::getUniformRandom()) / float(height - 1);
				ray = camera->getRay(u, v);
				color += getRayColor(ray, _scene, MAX_DEPTH);
			}

			color /= NUM_SAMPLES;

			image[(y * width + x) * 4 + 0] = sqrt(color.x);
			image[(y * width + x) * 4 + 1] = sqrt(color.y);
			image[(y * width + x) * 4 + 2] = sqrt(color.z);
			image[(y * width + x) * 4 + 3] = 1.0f;
		}
	}
}

vec3 RayTracer::getBackgroundColor(const Ray3D& ray)
{
	const vec3 rayDirection = glm::normalize(ray.getDirection());
	const float t = 0.5f * (rayDirection.y + 1.0f);		// [-1, 1] -> [0, 1]

	return (1.0f - t) * BACKGROUND_INTERP_COLOR_01 + t * BACKGROUND_INTERP_COLOR_02;
}

vec3 RayTracer::getRayColor(const Ray3D& ray, Scene* scene, int depth)
{
	Hittable::HitRecord record;

	if (depth <= 0) return vec3(.0f);

	if (_scene->hit(ray, .001f, FLT_MAX, record))
	{
		Ray3D scattered (vec3(.0f), vec3(.0f));
		vec3 attenuation;

		if (record._material->getApplicator()->scatter(record._material.get(), ray, record, attenuation, scattered))
		{
			return attenuation * this->getRayColor(scattered, scene, depth - 1);
		}
		
		return vec3(.0f);
	}

	return getBackgroundColor(ray);
}
