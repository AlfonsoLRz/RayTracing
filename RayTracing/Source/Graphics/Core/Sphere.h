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
	float						_radius;		//!<

protected:
	/**
	*	@brief Textures coordinates of a point based on theta and phi. 
	*/
	static vec2 getUV(const vec3& point);

public:
	/**
	*	@brief Constructor. 
	*/
	Sphere(const vec3& center, float radius, std::shared_ptr<Material> material);

	/**
	*	@brief
	*/
	virtual bool getBoundingBox(float time0, float time1, AABB& aabb) const;
	
	/**
	*	@brief
	*/
	virtual bool hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const;

	/**
	*	@return PDF over the surface.
	*/
	virtual float pdfValue(const vec3& origin, const vec3& direction) const;

	/**
	*	@return Outgoing direction from the origin of a surface.
	*/
	virtual vec3 random(const vec3& origin) const;
};

