#pragma once

#include "Geometry/3D/Ray3D.h"

/**
*	@file Hittable.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 15/04/2021
*/

/**
*	@brief---
*/
class Hittable
{
public:
	struct HitRecord
	{
		vec3	_normal;
		vec3	_point;
		float	_t;
	};

public:
	/**
	*	@brief  
	*/
	virtual bool hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const = 0;
};

