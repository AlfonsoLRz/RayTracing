#include "stdafx.h"
#include "Rectangle.h"

// [Public methods]

RectangleXY::RectangleXY(float x0, float x1, float y0, float y1, float z, std::shared_ptr<Material> material) :
	_x0(x0), _x1(x1), _y0(y0), _y1(y1), _z(z)
{
	this->_material = material;
}

bool RectangleXY::getBoundingBox(float time0, float time1, AABB& aabb) const
{
	aabb = AABB(vec3(_x0, _y0, _z - .0001f), vec3(_x1, _y1, _z + .0001f));
	return false;
}

bool RectangleXY::hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const
{
	float t = (_z - ray.getOrigin().z) / ray.getDirection().z;
	if (t < tMin || t > tMax) return false;

	float x = ray.getOrigin().x + t * ray.getDirection().x;
	float y = ray.getOrigin().y + t * ray.getDirection().y;
	if (x < _x0 || x > _x1 || y < _y0 || y > _y1) return false;

	hit._uv.x = (x - _x0) / (_x1 - _x0);
	hit._uv.y = (y - _y0) / (_y1 - _y0);
	hit._t = t;

	vec3 outwardNormal = vec3(.0f, .0f, 1.0f);
	hit.setFaceNormal(ray, outwardNormal);
	hit._material = this->_material;
	hit._point = ray.at(t);

	return true;
}
