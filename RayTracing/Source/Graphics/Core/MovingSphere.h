#pragma once

#include "Graphics/Core/Sphere.h"

/**
*	@file Sphere.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 15/04/2021
*/

/**
*	@brief
*/
class MovingSphere : public Sphere
{
protected:
	vec3	_center0, _center1;		//!<
	vec2	_timeFrame;				//!< Frame for sphere movement

protected:
	/**
	*	@brief Translates the sphere center according to a timestamp. 
	*/
	vec3 getCenter(float timestamp) const;

public:
	/**
	*	@brief Constructor.
	*/
	MovingSphere(const vec3& center01, const vec3& center02, float timestamp01, float timestamp02, float radius, std::shared_ptr<Material> material);

	/**
	*	@brief
	*/
	virtual bool hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const;
};
