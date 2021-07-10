#include "stdafx.h"
#include "HittableList.h"

// [Public methods]

void HittableList::buildBVH()
{
	_bvh = std::make_unique<BVH>(BVH(_hittableObjects, .0f, 1.0f));
}

bool HittableList::getBoundingBox(float time0, float time1, AABB& aabb) const
{
	if (_hittableObjects.empty()) return false;

	AABB tempAABB;

	for (std::shared_ptr<Hittable> object : _hittableObjects)
	{
		if (!object->getBoundingBox(time0, time1, tempAABB)) return false;
		aabb.update(tempAABB);
	}

	return true;
}

bool HittableList::hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const
{
	bool hitAnything = _bvh->hit(ray, tMin, tMax, hit);

	return hitAnything;
}

float HittableList::pdfValue(const vec3& origin, const vec3& direction) const
{
	float sumPDF = .0f;

	for (std::shared_ptr<Hittable> object : _hittableObjects)
	{
		sumPDF += object->pdfValue(origin, direction);
	}

	return sumPDF / _hittableObjects.size();
}

vec3 HittableList::random(const vec3& origin) const
{
	vec3 randomDirections = vec3(.0f);

	for (std::shared_ptr<Hittable> object : _hittableObjects)
	{
		randomDirections += object->random(origin);
	}

	return randomDirections / vec3(_hittableObjects.size());
}
