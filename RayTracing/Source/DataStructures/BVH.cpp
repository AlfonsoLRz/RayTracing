#include "stdafx.h"
#include "BVH.h"

// [BVH]

BVH::BVH(std::vector<std::shared_ptr<Hittable>>& objects, float time0, float time1)
{
	_root = std::make_unique<BVHNode>(new BVHNode(objects, 0, objects.size() - 1, time0, time1));
}

bool BVH::getBoundingBox(float time0, float time1, AABB& aabb)
{
	return _root->getBoundingBox(time0, time1, aabb);
}

bool BVH::hit(const Ray3D& ray, double tMin, double tMax, Hittable::HitRecord& hit)
{
	return _root->hit(ray, tMin, tMax, hit);
}

// [BVH node]

BVH::BVHNode::BVHNode()
{
}

BVH::BVHNode::BVHNode(std::vector<std::shared_ptr<Hittable>>& objects, unsigned start, unsigned end, float time0, float time1)
{
}

bool BVH::BVHNode::getBoundingBox(float time0, float time1, AABB& aabb) const
{
	return false;
}

bool BVH::BVHNode::hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const
{
	if (!_aabb.hit(ray, tMin, tMax))
	{
		return false;
	}

	bool hitLeft = _left->hit(ray, tMin, tMax, hit);
	bool hitRight = _right->hit(ray, tMin, tMax, hit);

	return hitLeft || hitRight;
}
