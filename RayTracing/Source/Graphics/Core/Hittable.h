#pragma once

#include "Geometry/3D/AABB.h"
#include "Geometry/3D/Ray3D.h"

/**
*	@file Hittable.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 15/04/2021
*/

class Material;

/**
*	@brief---
*/
class Hittable
{
public:
	struct HitRecord
	{
		bool						_frontFace;		//!<
		std::shared_ptr<Material>	_material;		//!<
		vec3						_normal;		//!<
		vec3						_point;			//!<
		float						_t;				//!<
		vec2						_uv;			//!< Texture coordinates

		/**
		*	@brief  
		*/
		void setFaceNormal(const Ray3D& ray, const vec3& outwardNormal);
	};

protected:
	std::shared_ptr<Material>	_material;		//!<

public:
	/**
	*	@brief
	*/
	virtual bool getBoundingBox(float time0, float time1, AABB& aabb) const = 0;
	
	/**
	*	@brief  
	*/
	virtual bool hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const = 0;
};

