#pragma once

/**
*	@file TransformedHittable.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 13/06/2021
*/

#include "Graphics/Core/Hittable.h"

/**
*	@brief 
*/
class TranslatedHittable: public Hittable
{
protected:
	std::shared_ptr<Hittable>	_hittable;		//!<
	vec3						_offset;		//!<

public:
	/**
	*	@brief Constructor of translated object, whose movement magnitude is equal to translation. 
	*/
	TranslatedHittable(std::shared_ptr<Hittable> hittablePtr, const vec3& translation);

	/**
	*	@brief
	*/
	virtual bool getBoundingBox(float time0, float time1, AABB& aabb) const;

	/**
	*	@brief
	*/
	virtual bool hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const;
};

/**
*	@brief
*/
class RotatedYHittable : public Hittable
{
protected:
	AABB						_aabb;						//!<
	float						_cosTheta, _sinTheta;		//!<
	bool						_hasBox;					//!<
	std::shared_ptr<Hittable>	_hittable;					//!<

public:
	/**
	*	@brief Constructor of an object rotated around Y axis.
	*/
	RotatedYHittable(std::shared_ptr<Hittable> hittablePtr, float angle);

	/**
	*	@brief
	*/
	virtual bool getBoundingBox(float time0, float time1, AABB& aabb) const;

	/**
	*	@brief
	*/
	virtual bool hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const;
};


