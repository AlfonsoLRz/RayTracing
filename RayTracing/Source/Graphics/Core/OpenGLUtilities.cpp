#include "stdafx.h"
#include "OpenGLUtilities.h"

/// [Static members initialization]

std::unique_ptr<VAO> _cubeVAO;
std::unique_ptr<VAO> _quadVAO;

/// [Public methods]

VAO* OpenGLPrimitives::getQuadVAO()
{
	if (!_quadVAO.get())
	{
		const std::vector<vec2> quadTextCoord{ vec2(0.0f, 0.0f), vec2(1.0f, 0.0f), vec2(0.0f, 1.0f), vec2(1.0f, 1.0f) };							// From texture coordinates we can compute position
		const std::vector<GLuint> triangleMesh{ 0, 1, 2, Model3D::RESTART_PRIMITIVE_INDEX, 1, 3, 2, Model3D::RESTART_PRIMITIVE_INDEX };				// Topology

		VAO* quadVAO = new VAO();
		quadVAO->setVBOData(CGEnumerations::VBO_TEXT_COORD, quadTextCoord);
		quadVAO->setIBOData(CGEnumerations::IBO_TRIANGLE_MESH, triangleMesh);

		_quadVAO.reset(quadVAO);
	}

	return _quadVAO.get();
}