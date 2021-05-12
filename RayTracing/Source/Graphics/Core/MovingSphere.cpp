#include "stdafx.h"
#include "MovingSphere.h"

// [Public methods]

MovingSphere::MovingSphere(const vec3& center01, const vec3& center02, float timestamp01, float timestamp02, float radius, std::shared_ptr<Material> material) :
	Sphere(center01, radius, material), _center0(center01), _center1(center02), _timeFrame(timestamp01, timestamp02)
{
}

bool MovingSphere::getBoundingBox(float time0, float time1, AABB& aabb) const
{
	aabb = AABB(getCenter(time0) - vec3(_radius), getCenter(time0) + vec3(_radius));
	aabb.update(AABB(getCenter(time1) - vec3(_radius), getCenter(time1) + vec3(_radius)));
	
	return true;
}

bool MovingSphere::hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const
{
	const vec3 center = getCenter(ray.getTimestamp());
	const vec3 oc = ray.getOrigin() - center;
	const float a = glm::length2(ray.getDirection());
	const float half_b = glm::dot(oc, ray.getDirection());
	const float c = glm::length2(oc) - _radius * _radius;
	const float discriminant = half_b * half_b - a * c;

	if (discriminant < .0f)
	{
		return false;
	}

	const float sqrtd = sqrt(discriminant);
	float root = (-half_b - sqrt(discriminant)) / a;

	if (root < tMin || root > tMax)
	{
		root = (-half_b + sqrt(discriminant)) / a;
		if (root < tMin || root > tMax)
		{
			return false;
		}
	}

	hit._t = root;
	hit._point = ray.at(root);
	hit._material = _material;

	vec3 outwardNormal = (hit._point - center) / _radius;
	hit.setFaceNormal(ray, outwardNormal);

	return true;
}

// [Protected methods]

vec3 MovingSphere::getCenter(float timestamp) const
{
	return _center0 + ((timestamp - _timeFrame.x) / (_timeFrame.y - _timeFrame.x)) * (_center1 - _center0);
}