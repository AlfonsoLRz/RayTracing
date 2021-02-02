#pragma once

#include "stdafx.h"

/**
*	@file GraphicsCoreEnumerations.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 01/02/2021
*/

/**
*	@brief Struct which wraps all that information for a mesh vertex.
*/
struct VertexGPUData
{
	vec3		_position;
	float		_padding1;

	vec3		_normal;
	float		_padding2;

	vec2		_textCoord;
	vec2		_padding3;

	vec3		_tangent;
	float		_padding4;
};

/**
*	@brief Struct which wraps a mesh data.
*/
struct FaceGPUData
{
	uvec3		_vertices;
	unsigned	_modelCompID;							//!< ID of model component where the face belongs to

	vec3		_minPoint;								//!< Bounding box corner
	float		_padding1;

	vec3		_maxPoint;
	float		_padding2;

	vec3		_normal;								//!< Accelerates LiDAR intersections 
	float		_padding3;
};
