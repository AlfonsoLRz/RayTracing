#include "stdafx.h"
#include "ShaderList.h"

// [Static members initialization]

std::unordered_map<uint8_t, std::string> ShaderList::COMPUTE_SHADER_SOURCE {
		{CGEnumerations::BIT_MASK_RADIX_SORT, "Assets/Shaders/Compute/LiDAR/addOutlier"}
};

std::unordered_map<uint8_t, std::string> ShaderList::RENDERING_SHADER_SOURCE {
		{CGEnumerations::REND_TO_QUAD_SHADER, "Assets/Shaders/2D/renderQuad"}
};

std::vector<std::unique_ptr<ComputeShader>> ShaderList::_computeShader (CGEnumerations::numComputeShaderTypes());
std::vector<std::unique_ptr<RenderingShader>> ShaderList::_renderingShader (CGEnumerations::numRenderingShaderTypes());

/// [Protected methods]

ShaderList::ShaderList()
{
}

/// [Public methods]

ComputeShader* ShaderList::getComputeShader(const CGEnumerations::ComputeShaderTypes shader)
{
	const int shaderID = shader;

	if (!_computeShader[shader].get())
	{
		ComputeShader* shader = new ComputeShader();
		shader->createShaderProgram(COMPUTE_SHADER_SOURCE.at(shaderID).c_str());

		_computeShader[shaderID].reset(shader);
	}

	return _computeShader[shaderID].get();
}

RenderingShader* ShaderList::getRenderingShader(const CGEnumerations::RenderingShaderTypes shader)
{
	const int shaderID = shader;

	if (!_renderingShader[shader].get())
	{
		RenderingShader* shader = new RenderingShader();
		shader->createShaderProgram(RENDERING_SHADER_SOURCE.at(shaderID).c_str());

		_renderingShader[shaderID].reset(shader);
	}

	return _renderingShader[shader].get();
}
