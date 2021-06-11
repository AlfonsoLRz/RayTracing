#pragma once

#include "DataStructures/BVH.h"
#include "Graphics/Core/Hittable.h"

/**
*	@file HittableList.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 11/06/2021
*/

/**
*	@brief
*/
class HittableList: public Hittable
{
protected:
	std::unique_ptr<BVH>					_bvh;							//!<
	std::vector<std::shared_ptr<Hittable>>	_hittableObjects;				//!<

public:
	/**
	*	@brief
	*/
	void addObject(std::shared_ptr<Hittable> object) { _hittableObjects.push_back(object); }

	/**
	*	@brief  
	*/
	void buildBVH();

	/**
	*	@brief
	*/
	void clearObjects() { _hittableObjects.clear(); }
	
	/**
	*	@brief
	*/
	virtual bool getBoundingBox(float time0, float time1, AABB& aabb) const;

	/**
	*	@brief
	*/
	virtual bool hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const;
};

