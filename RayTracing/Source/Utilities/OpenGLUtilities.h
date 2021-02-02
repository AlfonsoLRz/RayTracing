#pragma once

#include "Graphics/Core/VAO.h"

/**
*	@file OpenGLUtilities.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 01/02/2021
*/

/**
*	@brief Several operations which can be useful for different entities.
*/
namespace OpenGLUtilities
{
};

class Primitives
{
protected:
	static std::unique_ptr<VAO> QUAD_VAO;
	static std::unique_ptr<VAO> CUBE_VAO;

public:
	/**
	*	@return Eight points which represents the given cube.
	*/
	static std::vector<vec4> getCubePoints(const vec3& minValues, const vec3& maxValues);

	/**
	*	@return Vector of indices which represents the cube wireframe shape.
	*/
	static std::vector<GLuint> getCubeWireframeIndices(const unsigned startIndex);

	/**
	*	@return VAO with geometry and topology of a cube.
	*/
	static VAO* getCubeVAO();

	/**
	*	@return VAO with geometry and topology of a quad.
	*/
	static VAO* getQuadVAO();
};



