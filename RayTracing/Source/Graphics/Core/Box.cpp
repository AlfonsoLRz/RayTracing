#include "stdafx.h"
#include "Box.h"

// [Public methods]

Box::Box(const vec3& point0, const vec3& point1, std::shared_ptr<Material> material) :
	_aabb(point0, point1), Hittable(material)
{
}

bool Box::getBoundingBox(float time0, float time1, AABB& aabb) const
{
	aabb = AABB(_aabb);
	return true;
}

bool Box::hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const
{

}
