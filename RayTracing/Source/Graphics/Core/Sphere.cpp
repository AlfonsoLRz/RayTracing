#include "stdafx.h"
#include "Sphere.h"

// [Public methods]

Sphere::Sphere(const vec3& center, float radius, std::shared_ptr<Material> material) : _center(center), _material(material), _radius(radius)
{
}

bool Sphere::getBoundingBox(float time0, float time1, AABB& aabb) const
{
	aabb = AABB(_center - vec3(_radius), _center + vec3(_radius));	
	return true;
}

bool Sphere::hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const
{
	const vec3 oc = ray.getOrigin() - _center;
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
	
	vec3 outwardNormal = (hit._point - _center) / _radius;
	hit.setFaceNormal(ray, outwardNormal);
	hit._uv = getUV(outwardNormal);

	return true;
}

// [Protected methods]

vec2 Sphere::getUV(const vec3& point)
{
	float theta = std::acos(-point.y);
	float phi = std::atan2(-point.z, point.x) + glm::pi<float>();

	return vec2(phi / (2.0f * glm::pi<float>()), theta / glm::pi<float>());
}
