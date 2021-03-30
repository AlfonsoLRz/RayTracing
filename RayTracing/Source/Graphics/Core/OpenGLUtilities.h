#pragma once

#include "stdafx.h"
#include "Graphics/Core/VAO.h"

/**
*	@file OpenGLUtilities.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 08/03/2019
*/

/**
*	@brief Several operations which can be useful for different entities.
*/
class OpenGLPrimitives
{
protected:
	static std::unique_ptr<VAO> QUAD_VAO;

public:
	/**
	*	@return VAO with geometry and topology of a quad.
	*/
	static VAO* getQuadVAO();
};



