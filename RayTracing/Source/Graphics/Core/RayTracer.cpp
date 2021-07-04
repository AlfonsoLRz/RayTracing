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
				color += getRayColor(ray, BACKGROUND_COLOR, _scene, MAX_DEPTH);
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

vec3 RayTracer::getRayColor(const Ray3D& ray, const vec3& background, Scene* scene, int depth)
{
	Hittable::HitRecord record;

	if (depth <= 0) return vec3(.0f);

	if (!_scene->hit(ray, .001f, FLT_MAX, record))
	{
		return background;
	}

	Ray3D scattered(vec3(.0f), vec3(.0f));
	vec3 attenuation;
	vec3 emitted = record._material->getApplicator()->emit(record._material.get(), record._uv, record._point);
	float pdf = .0f;

	if (!record._material->getApplicator()->scatter(record._material.get(), ray, record, attenuation, scattered, pdf))
	{
		return emitted;
	}

	vec3 lightPosition = vec3(RandomUtilities::getUniformRandom(213.0f, 343.0f), 554.0f, RandomUtilities::getUniformRandom(227.0f, 332.0f));
	vec3 lightDirection = lightPosition - record._point;
	float distanceSquared = glm::length2(lightDirection);
	lightDirection = glm::normalize(lightDirection);

	if (glm::dot(lightDirection, record._normal) < .0f)
	{
		return emitted;
	}

	float lightArea = (343.0f - 213.0f) * (332.0f - 227.0f);
	float lightCosine = fabs(lightDirection.y);
	if (lightCosine < glm::epsilon<float>())
	{
		return emitted;
	}

	pdf = distanceSquared / (lightCosine * lightArea);
	scattered = Ray3D(record._point, lightDirection, ray.getTimestamp());

	return emitted + attenuation * record._material->getApplicator()->scatterPDF(ray, record, scattered) * 
								   this->getRayColor(scattered, background, scene, depth - 1) / pdf;
}
