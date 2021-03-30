#pragma once

#include "stdafx.h"

/**
*	@file GraphicsCoreEnumerations.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 01/02/2021
*/

/**
*	@brief Contains any enum related to rendering process.
*/
struct CGEnumerations
{
	/// [Geometry and topology]

	// Topology types
	enum IBOTypes: uint8_t
	{
		IBO_POINT_CLOUD,
		IBO_WIREFRAME,
		IBO_TRIANGLE_MESH
	};

	// Geometry types
	enum VBOTypes : uint8_t
	{
		VBO_POSITION,
		VBO_NORMAL,
		VBO_TEXT_COORD,
		VBO_TANGENT
	};

	/**
	*	@return Number of VBO different types.
	*/
	const static GLsizei numIBOTypes() { return IBO_TRIANGLE_MESH + 1; }

	/**
	*	@return Number of VBO different types.
	*/
	const static GLsizei numVBOTypes() { return VBO_TANGENT + 1; }

	/// [Shaders]

	// Shader implementations
	enum RenderingShaderTypes : uint8_t
	{
		REND_TO_QUAD_SHADER
	};

	enum ComputeShaderTypes : uint8_t
	{
		// BVH
		BUILD_CLUSTER_BUFFER,
		CLUSTER_MERGING,
		COMPUTE_FACE_AABB,
		COMPUTE_GROUP_AABB,
		COMPUTE_MORTON_CODES,
		DOWN_SWEEP_PREFIX_SCAN,
		FIND_BEST_NEIGHBOR,
		REALLOCATE_CLUSTERS,
		REDUCE_PREFIX_SCAN,
		RESET_LAST_POSITION_PREFIX_SCAN,

		// Radix sort
		BIT_MASK_RADIX_SORT,
		END_LOOP_COMPUTATIONS,
		REALLOCATE_RADIX_SORT,
		RESET_BUFFER_INDEX
	};

	/**
	*	@return Number of compute shaders.
	*/
	const static GLsizei numComputeShaderTypes() { return REND_TO_QUAD_SHADER + 1; }

	/**
	*	@return Number of rendering shaders.
	*/
	const static GLsizei numRenderingShaderTypes() { return RESET_BUFFER_INDEX + 1; }

	/// [Rendering parameters]

	// Matrices types
	enum MatricesTypes : uint8_t
	{
		MODEL_MATRIX,
		VIEW_MATRIX,
		PROJ_MATRIX,
		VIEW_PROJ_MATRIX,
		BIAS_VIEW_PROJ_MATRIX
	};

	/**
	*	@return Number of rendering shaders.
	*/
	const static GLsizei numMatricesTypes() { return BIAS_VIEW_PROJ_MATRIX + 1; }
};