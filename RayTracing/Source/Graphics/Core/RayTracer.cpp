#include "stdafx.h"
#include "RayTracer.h"

#include "Graphics/Core/PDF.h"
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

			// Check for NaNs
			if (color.x != color.x) color.x = .0f;
			if (color.y != color.y) color.y = .0f;
			if (color.z != color.z) color.z = .0f;

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
	MaterialType::ScatterRecord scatterRecord;

	if (depth <= 0) return vec3(.0f);

	if (!_scene->hit(ray, .001f, FLT_MAX, record))
	{
		return background;
	}

	Ray3D scattered(vec3(.0f), vec3(.0f));
	vec3 emitted = record._material->getApplicator()->emit(record._material.get(), record, record._uv, record._point);
	float pdf = .0f;

	if (!record._material->getApplicator()->scatter(record._material.get(), ray, record, scatterRecord))
	{
		return emitted;
	}

	if (scatterRecord._isSpecular)
	{
		return scatterRecord._attenuation * this->getRayColor(scatterRecord._specularRay, background, scene, depth - 1);
	}
	
	std::shared_ptr<HittablePDF> lightPDF = std::make_shared<HittablePDF>(_scene->getLights(), record._point);
	std::shared_ptr<MixturePDF> mixturePDF = std::make_shared<MixturePDF>(scatterRecord._pdf, lightPDF);
	
	scattered = Ray3D(record._point, mixturePDF->generate(), ray.getTimestamp());
	pdf = mixturePDF->value(scattered.getDirection());

	return emitted + scatterRecord._attenuation * record._material->getApplicator()->scatterPDF(ray, record, scattered) * this->getRayColor(scattered, background, scene, depth - 1) / pdf;
}
