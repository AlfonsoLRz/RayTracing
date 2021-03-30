#pragma once

#include "Graphics/Core/CGEnumerations.h"
#include "Graphics/Core/ComputeShader.h"
#include "Graphics/Core/RenderingShader.h"
#include "Utilities/Singleton.h"

/**
*	@file ShaderList.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 28/03/2021
*/

/**
*	@brief Maintains a list of shaders which are globally accessible.
*/
class ShaderList: public Singleton<ShaderList>
{
	friend class Singleton<ShaderList>;

protected:
	static std::unordered_map<uint8_t, std::string> COMPUTE_SHADER_SOURCE;					//!< Path from where we can get each compute shader
	static std::unordered_map<uint8_t, std::string> RENDERING_SHADER_SOURCE;					//!< Path from where we can get each rendering shader

protected:
	static std::vector<std::unique_ptr<ComputeShader>>		_computeShader;				//!< Already loaded compute shaders
	static std::vector<std::unique_ptr<RenderingShader>>	_renderingShader;			//!< Already loaded rendering shader

protected:
	/**
	*	@brief Default constructor.
	*/
	ShaderList();

public:
	/**
	*	@return Compute shader defined by the identifier.
	*/
	ComputeShader* getComputeShader(const CGEnumerations::ComputeShaderTypes shader);

	/**
	*	@return Rendering shader defined by the identifier.
	*/
	RenderingShader* getRenderingShader(const CGEnumerations::RenderingShaderTypes shader);
};

