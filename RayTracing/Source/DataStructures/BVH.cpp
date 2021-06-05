#include "stdafx.h"
#include "BVH.h"

#include "Utilities/RandomUtilities.h"

// [BVH]

BVH::BVH(std::vector<std::shared_ptr<Hittable>>& objects, float time0, float time1)
{
	_root = std::make_unique<BVHNode>(BVHNode(objects, 0, objects.size(), time0, time1));
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
	// Build BVH
	auto objectsCopy = objects;
	int axis = RandomUtilities::getUniformRandomInt(0, 2);
	auto comparator = (axis == 0) ? BVHNode::boxCompare_x : (axis == 1) ? BVHNode::boxCompare_y : BVHNode::boxCompare_z;
	size_t objectSpan = end - start;

	if (objectSpan == 1)
	{
		_left = _right = objectsCopy[start];
	}
	else if (objectSpan == 2)
	{
		if (comparator(objectsCopy[start], objectsCopy[start + 1]))
		{
			_left = objectsCopy[start];
			_right = objectsCopy[start + 1];
		}
		else
		{
			_right = objectsCopy[start];
			_left = objectsCopy[start + 1];
		}
	}
	else
	{
		std::sort(objectsCopy.begin() + start, objectsCopy.begin() + end, comparator);
		int mid = start + objectSpan / 2;

		_left = std::make_shared<BVHNode>(BVHNode(objectsCopy, start, mid, time0, time1));
		_right = std::make_shared<BVHNode>(BVHNode(objectsCopy, mid, end, time0, time1));
	}

	// Calculate surrounding box
	AABB boxLeft, boxRight;
	_left->getBoundingBox(time0, time1, boxLeft);
	_right->getBoundingBox(time0, time1, boxRight);
	
	_aabb.update(boxLeft);
	_aabb.update(boxRight);
}

bool BVH::BVHNode::getBoundingBox(float time0, float time1, AABB& aabb) const
{
	aabb = _aabb;
	return true;
}

bool BVH::BVHNode::hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const
{
	if (!_aabb.hit(ray, tMin, tMax))
	{
		return false;
	}

	bool hitLeft = _left->hit(ray, tMin, tMax, hit);
	bool hitRight = _right->hit(ray, tMin, hitLeft ? hit._t : tMax, hit);

	return hitLeft || hitRight;
}

// Box comparison functions

bool BVH::BVHNode::boxCompare(const std::shared_ptr<Hittable> h1, const std::shared_ptr<Hittable> h2, int axis)
{
	AABB box01, box02;
	h1->getBoundingBox(0, 0, box01);
	h2->getBoundingBox(0, 0, box02);

	return box01.min()[axis] < box02.min()[axis];
}

bool BVH::BVHNode::boxCompare_x(const std::shared_ptr<Hittable> h1, const std::shared_ptr<Hittable> h2)
{
	return boxCompare(h1, h2, 0);
}

bool BVH::BVHNode::boxCompare_y(const std::shared_ptr<Hittable> h1, const std::shared_ptr<Hittable> h2)
{
	return boxCompare(h1, h2, 1);
}

bool BVH::BVHNode::boxCompare_z(const std::shared_ptr<Hittable> h1, const std::shared_ptr<Hittable> h2)
{
	return boxCompare(h1, h2, 2);
}