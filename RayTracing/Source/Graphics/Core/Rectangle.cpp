#include "stdafx.h"
#include "Rectangle.h"

#include "Utilities/RandomUtilities.h"

// [Rectangle XZ]

RectangleXY::RectangleXY(float x0, float x1, float y0, float y1, float z, std::shared_ptr<Material> material) :
	_x0(x0), _x1(x1), _y0(y0), _y1(y1), _z(z), Hittable(material)
{
}

bool RectangleXY::getBoundingBox(float time0, float time1, AABB& aabb) const
{
	aabb = AABB(vec3(_x0, _y0, _z - .0001f), vec3(_x1, _y1, _z + .0001f));
	return true;
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

	this->flipRecordNormals(hit);

	return true;
}

// [Rectangle XZ]

RectangleXZ::RectangleXZ(float x0, float x1, float z0, float z1, float y, std::shared_ptr<Material> material) :
	_x0(x0), _x1(x1), _z0(z0), _z1(z1), _y(y), Hittable(material)
{
}

bool RectangleXZ::getBoundingBox(float time0, float time1, AABB& aabb) const
{
	aabb = AABB(vec3(_x0, _y - .0001f, _z0), vec3(_x1, _y + .0001f, _z1));
	return true;
}

bool RectangleXZ::hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const
{
	float t = (_y - ray.getOrigin().y) / ray.getDirection().y;
	if (t < tMin || t > tMax) return false;

	float x = ray.getOrigin().x + t * ray.getDirection().x;
	float z = ray.getOrigin().z + t * ray.getDirection().z;
	if (x < _x0 || x > _x1 || z < _z0 || z > _z1) return false;

	hit._uv.x = (x - _x0) / (_x1 - _x0);
	hit._uv.y = (z - _z0) / (_z1 - _z0);
	hit._t = t;

	vec3 outwardNormal = vec3(.0f, 1.0f, .0f);
	hit.setFaceNormal(ray, outwardNormal);
	hit._material = this->_material;
	hit._point = ray.at(t);

	this->flipRecordNormals(hit);

	return true;
}

float RectangleXZ::pdfValue(const vec3& origin, const vec3& direction) const
{
	HitRecord record;

	if (!this->hit(Ray3D(origin, direction), .001f, FLT_MAX, record))
	{
		return .0f;
	}

	const float area = (_x1 - _x0) * (_z1 - _z0);
	const float distanceSquared = record._t * record._t * glm::length2(direction);
	const float cosine = glm::abs(glm::dot(direction, record._normal) / glm::length(direction));

	return distanceSquared / (cosine * area);
}

vec3 RectangleXZ::random(const vec3& origin) const
{
	const vec3 randomPoint = vec3(RandomUtilities::getUniformRandom(_x0, _x1), _y, RandomUtilities::getUniformRandom(_z0, _z1));
	return randomPoint - origin;
}

// [Rectangle YZ]

RectangleYZ::RectangleYZ(float y0, float y1, float z0, float z1, float x, std::shared_ptr<Material> material) :
	_y0(y0), _y1(y1), _z0(z0), _z1(z1), _x(x), Hittable(material)
{
}

bool RectangleYZ::getBoundingBox(float time0, float time1, AABB& aabb) const
{
	aabb = AABB(vec3(_x - .0001f, _y0, _z0), vec3(_x + .0001f, _y1, _z1));
	return true;
}

bool RectangleYZ::hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const
{
	float t = (_x - ray.getOrigin().x) / ray.getDirection().x;
	if (t < tMin || t > tMax) return false;

	float y = ray.getOrigin().y + t * ray.getDirection().y;
	float z = ray.getOrigin().z + t * ray.getDirection().z;
	if (y < _y0 || y > _y1 || z < _z0 || z > _z1) return false;

	hit._uv.x = (y - _y0) / (_y1 - _y0);
	hit._uv.y = (z - _z0) / (_z1 - _z0);
	hit._t = t;

	vec3 outwardNormal = vec3(1.0f, .0f, .0f);
	hit.setFaceNormal(ray, outwardNormal);
	hit._material = this->_material;
	hit._point = ray.at(t);

	this->flipRecordNormals(hit);

	return true;
}
