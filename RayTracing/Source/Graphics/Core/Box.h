#pragma once

#include "Graphics/Core/Hittable.h"

/**
*	@file Box.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 11/06/2021
*/

/**
*	@brief
*/
class Box: public Hittable
{
protected:
	AABB _aabb;		//!<

public:
	/**
	*	@brief Constructor.
	*/
	Box(const vec3& point0, const vec3& point1, std::shared_ptr<Material> material);

	/**
	*	@brief
	*/
	virtual bool getBoundingBox(float time0, float time1, AABB& aabb) const;

	/**
	*	@brief
	*/
	virtual bool hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const;
};

