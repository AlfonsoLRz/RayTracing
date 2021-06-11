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
	float _x0, _x1, _y0, _y1, _z;		//!< Boundaries of a rectangle aligned to XY plane

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

/**
*	@brief
*/
class RectangleXZ : public Hittable
{
protected:
	float _x0, _x1, _z0, _z1, _y;		//!< Boundaries of a rectangle aligned to XZ plane

public:
	/**
	*	@brief
	*/
	RectangleXZ(float x0, float x1, float z0, float z1, float y, std::shared_ptr<Material> material);

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
class RectangleYZ : public Hittable
{
protected:
	float _y0, _y1, _z0, _z1, _x;		//!< Boundaries of a rectangle aligned to XZ plane

public:
	/**
	*	@brief
	*/
	RectangleYZ(float y0, float y1, float z0, float z1, float x, std::shared_ptr<Material> material);

	/**
	*	@brief
	*/
	virtual bool getBoundingBox(float time0, float time1, AABB& aabb) const;

	/**
	*	@brief
	*/
	virtual bool hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const;
};

