#include "stdafx.h"
#include "Box.h"

#include "Graphics/Core/Rectangle.h"

// [Public methods]

Box::Box(const vec3& point0, const vec3& point1, std::shared_ptr<Material> material) :
	_aabb(point0, point1), Hittable(material)
{
	_hittableList.reset(new HittableList);
	
	_hittableList->addObject(std::make_shared<RectangleXY>(point0.x, point1.x, point0.y, point1.y, point0.z, material));
	_hittableList->addObject(std::make_shared<RectangleXY>(point0.x, point1.x, point0.y, point1.y, point1.z, material));

	_hittableList->addObject(std::make_shared<RectangleXZ>(point0.x, point1.x, point0.z, point1.z, point0.y, material));
	_hittableList->addObject(std::make_shared<RectangleXZ>(point0.x, point1.x, point0.z, point1.z, point1.y, material));

	_hittableList->addObject(std::make_shared<RectangleYZ>(point0.y, point1.y, point0.z, point1.z, point0.x, material));
	_hittableList->addObject(std::make_shared<RectangleYZ>(point0.y, point1.y, point0.z, point1.z, point1.x, material));

	_hittableList->buildBVH();
}

bool Box::getBoundingBox(float time0, float time1, AABB& aabb) const
{
	aabb = AABB(_aabb);
	return true;
}

bool Box::hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const
{
	return _hittableList->hit(ray, tMin, tMax, hit);
}
