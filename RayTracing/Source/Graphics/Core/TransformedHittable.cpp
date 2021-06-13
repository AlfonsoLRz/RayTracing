#include "stdafx.h"
#include "TransformedHittable.h"

// [TranslatedHittable]

TranslatedHittable::TranslatedHittable(std::shared_ptr<Hittable> hittablePtr, const vec3& translation) :
	_hittable(hittablePtr), _offset(translation)
{
}

bool TranslatedHittable::getBoundingBox(float time0, float time1, AABB& aabb) const
{
	if (!_hittable->getBoundingBox(time0, time1, aabb))
	{
		return false;
	}

	aabb = AABB(aabb.min() + _offset, aabb.max() + _offset);

	return true;
}

bool TranslatedHittable::hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const
{
	Ray3D translatedRay(ray.getOrigin() - _offset, ray.getDirection(), ray.getTimestamp());
	if (!_hittable->hit(translatedRay, tMin, tMax, hit))
	{
		return false;
	}

	hit._point += _offset;
	hit.setFaceNormal(translatedRay, hit._normal);

	return true;
}

// [RotatedYHittable]

RotatedYHittable::RotatedYHittable(std::shared_ptr<Hittable> hittablePtr, float angle) :
	_hittable(hittablePtr)
{
	vec3 minPoint(FLT_MAX), maxPoint(-FLT_MAX);
	float radians = glm::radians(angle);
	_sinTheta = glm::sin(radians);
	_cosTheta = glm::cos(radians);
	_hasBox = _hittable->getBoundingBox(0, 1, _aabb);

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				float x = i * _aabb.max().x + (1 - i) * _aabb.min().x;
				float y = j * _aabb.max().y + (1 - j) * _aabb.min().y;
				float z = k * _aabb.max().z + (1 - k) * _aabb.min().z;
				float newx = _cosTheta * x + _sinTheta * z;
				float newz = -_sinTheta * x + _cosTheta * z;
				vec3 tester(newx, y, newz);

				for (int c = 0; c < 3; ++c)
				{
					minPoint[c] = glm::min(minPoint[c], tester[c]);
					maxPoint[c] = glm::max(maxPoint[c], tester[c]);
				}
			}
		}
	}

	_aabb = AABB(minPoint, maxPoint);
}

bool RotatedYHittable::getBoundingBox(float time0, float time1, AABB& aabb) const
{
	aabb = AABB(_aabb);
	return _hasBox;
}

bool RotatedYHittable::hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const
{
	vec3 rayOrigin = ray.getOrigin(), rayDirection = ray.getDirection();
	rayOrigin[0] = _cosTheta * ray.getOrigin()[0] - _sinTheta * ray.getOrigin()[2];
	rayOrigin[2] = _sinTheta * ray.getOrigin()[0] + _cosTheta * ray.getOrigin()[2];
	rayDirection[0] = _cosTheta * ray.getDirection()[0] - _sinTheta * ray.getDirection()[2];
	rayDirection[2] = _sinTheta * ray.getDirection()[0] + _cosTheta * ray.getDirection()[2];

	Ray3D rotatedRay(rayOrigin, rayDirection, ray.getTimestamp());
	if (!_hittable->hit(rotatedRay, tMin, tMax, hit))
	{
		return false;
	}

	vec3 point = hit._point, normal = hit._normal;
	point[0] = _cosTheta * hit._point[0] + _sinTheta * hit._point[2];
	point[2] = -_sinTheta * hit._point[0] + _cosTheta * hit._point[2];
	normal[0] = _cosTheta * hit._normal[0] + _sinTheta * hit._normal[2];
	normal[2] = -_sinTheta * hit._normal[0] + _cosTheta * hit._normal[2];

	hit._point = point;
	hit.setFaceNormal(rotatedRay, normal);

	return true;
}
