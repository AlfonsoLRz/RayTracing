#pragma once

/**
*	@file BoxConstantMediumh
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 21/06/2021
*/

#include "Graphics/Core/Hittable.h"
#include "Graphics/Core/Texture.h"

/**
*	@brief 
*/
class ConstantMedium: public Hittable
{
private:
	std::shared_ptr<Hittable>	_boundary;						//!<
	float						_negativeInverseDensity;		//!<
	std::shared_ptr<Material>	_phaseFunction;					//!<

public:
	/**
	*	@brief Constructor of a constant medium from a texture.
	*/
	ConstantMedium(std::shared_ptr<Hittable> boundary, std::shared_ptr<Texture> albedo, double density);

	/**
	*	@brief Constructor of a constant medium from a constant color.
	*/
	ConstantMedium(std::shared_ptr<Hittable> boundary, const vec3& color, double density);

	/**
	*	@brief
	*/
	virtual bool getBoundingBox(float time0, float time1, AABB& aabb) const;

	/**
	*	@brief
	*/
	virtual bool hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const;
};

