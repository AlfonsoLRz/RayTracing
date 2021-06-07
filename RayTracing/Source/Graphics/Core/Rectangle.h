#pragma once

#include "Graphics/Core/Hittable.h"

/**
*	@file Rectangle.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 07/06/2021
*/

/**
*	@brief
*/
class RectangleXY: public Hittable
{
protected:
	float _x0, _x1, _y0, _y1, _z;		//!< Boundaries of a rectangle aligned to XY plane.

public:
	/**
	*	@brief  
	*/
	RectangleXY(float x0, float x1, float y0, float y1, float z, std::shared_ptr<Material> material);
	
	/**
	*	@brief
	*/
	virtual bool getBoundingBox(float time0, float time1, AABB& aabb) const;

	/**
	*	@brief
	*/
	virtual bool hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const;
};

