#pragma once

#include "Geometry/3D/AABB.h"
#include "Graphics/Core/Hittable.h"

/**
*	@file BVH.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 12/05/2021
*/

/**
*	@brief Boundary Volume Hierarchy implementation.
*/
class BVH
{
protected:
	class BVHNode;

protected:
	std::unique_ptr<BVHNode> _root;		//!< Tree root

public:
	/**
	*	@brief  
	*/
	BVH(std::vector<std::shared_ptr<Hittable>>& objects, float time0, float time1);
	
	/**
	*	@brief
	*/
	bool getBoundingBox(float time0, float time1, AABB& aabb);

	/**
	*	@brief
	*/
	bool hit(const Ray3D& ray, double tMin, double tMax, Hittable::HitRecord& hit);

protected:
	/**
	*	@brief 
	*/
	class BVHNode: public Hittable
	{
		AABB						_aabb;				//!<
		std::shared_ptr<Hittable>	_left, _right;		//!< Pointers to children nodes

	public:
		/**
		*	@brief
		*/
		static bool boxCompare(const std::shared_ptr<Hittable> h1, const std::shared_ptr<Hittable> h2, int axis);

		/**
		*	@brief
		*/
		static bool boxCompare_x(const std::shared_ptr<Hittable> h1, const std::shared_ptr<Hittable> h2);

		/**
		*	@brief
		*/
		static bool boxCompare_y(const std::shared_ptr<Hittable> h1, const std::shared_ptr<Hittable> h2);

		/**
		*	@brief
		*/
		static bool boxCompare_z(const std::shared_ptr<Hittable> h1, const std::shared_ptr<Hittable> h2);
	
	public:
		/**
		*	@brief Default constructor. 
		*/
		BVHNode();

		/**
		*	@brief  
		*/
		BVHNode(std::vector<std::shared_ptr<Hittable>>& objects, unsigned start, unsigned end, float time0, float time1);

		/**
		*	@brief
		*/
		virtual bool getBoundingBox(float time0, float time1, AABB& aabb) const;

		/**
		*	@brief
		*/
		virtual bool hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const;
	};
};

