#include "stdafx.h"
#include "RayTracer.h"

#include "Graphics/Core/ShaderList.h"
#include "Graphics/Core/Sphere.h"
#include "Interface/Window.h"

// [Public methods]

RayTracer::~RayTracer()
{
	delete _rayTracingImage;
}

void RayTracer::renderFrame()
{
	VAO* quadVAO = OpenGLPrimitives::getQuadVAO();
	Texture* image = _rayTracingImage->getTexture();

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

	// [Camera]
	Camera* camera =_scene->getCameraManager()->getActiveCamera();
	const vec3 origin = camera->getEye();
	const float focalLength = 1.0f;
	const float viewportHeight = 4.0f;
	const float viewportWidth = viewportHeight * width / height;
	const vec3 horizontal = vec3(viewportWidth, .0f, .0f), vertical = vec3(.0f, viewportHeight, .0f);
	const vec3 lowerLeftCorner = origin - horizontal / 2.0f - vertical / 2.0f - vec3(.0f, .0f, focalLength);

	for (unsigned x = 0; x < width; ++x)
	{
		for (unsigned y = 0; y < height; ++y)
		{
			float u = x / float(width - 1), v = y / float(height - 1);
			Ray3D ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
			vec3 color = getBackgroundColor(ray);

			Hittable::HitRecord record;
			if (_scene->hit(ray, .0f, FLT_MAX, record))
			{
				color = (record._normal + vec3(1.0f)) / 2.0f;
			}

			image[(y * width + x) * 4 + 0] = color.x;
			image[(y * width + x) * 4 + 1] = color.y;
			image[(y * width + x) * 4 + 2] = color.z;
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
