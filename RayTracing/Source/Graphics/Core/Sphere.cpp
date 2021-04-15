#include "stdafx.h"
#include "Sphere.h"

// [Public methods]

Sphere::Sphere(const vec3& center, float radius) : _center(center), _radius(radius)
{
}

bool Sphere::hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const
{
	const vec3 oc = ray.getOrigin() - _center;
	const float a = glm::dot(ray.getDirection(), ray.getDirection());
	const float b = 2.0f * glm::dot(oc, ray.getDirection());
	const float c = glm::dot(oc, oc) - _radius * _radius;
	const float discriminant = b * b - 4 * a * c;

	return discriminant > 0;
}
