#pragma once

#include "Graphics/Core/Hittable.h"

/**
*	@file Sphere.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 15/04/2021
*/

/**
*	@brief 
*/
class Sphere: public Hittable
{
protected:
	vec3						_center;		//!<
	std::shared_ptr<Material>	_material;		//!<
	float						_radius;		//!<

public:
	/**
	*	@brief Constructor. 
	*/
	Sphere(const vec3& center, float radius, std::shared_ptr<Material> material);
	
	/**
	*	@brief
	*/
	virtual bool hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const;
};

