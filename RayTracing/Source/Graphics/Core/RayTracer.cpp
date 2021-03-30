#include "stdafx.h"
#include "RayTracer.h"

#include "Graphics/Core/ShaderList.h"
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

void RayTracer::updateSize(const uint16_t width, const uint16_t height)
{
	_rayTracingImage->updateSize(width, height);
	_rayTracingImage->updateRenderingBuffers();
}

// [Protected methods]

RayTracer::RayTracer()
{
	const ivec2 canvasSize = Window::getInstance()->getSize();
	
	_rayTracingImage = new FloatImage(canvasSize.x, canvasSize.y, 4);
	_quadVAO = OpenGLPrimitives::getQuadVAO();
}

void RayTracer::drawDebugTexture()
{
	const unsigned width = _rayTracingImage->getWidth(), height = _rayTracingImage->getHeight();
	float* image = _rayTracingImage->bits();

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			image[(y * width + x) * 4 + 0] = float(x) / (width - 1);
			image[(y * width + x) * 4 + 1] = float(y) / (height - 1);
			image[(y * width + x) * 4 + 2] = 0.25f;
			image[(y * width + x) * 4 + 3] = 1.0f;
		}
	}
}
