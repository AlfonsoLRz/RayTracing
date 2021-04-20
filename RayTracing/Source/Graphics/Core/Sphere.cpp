#include "stdafx.h"
#include "Sphere.h"

// [Public methods]

Sphere::Sphere(const vec3& center, float radius, std::shared_ptr<Material> material) : _center(center), _material(material), _radius(radius)
{
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
	
	vec3 outwardNormal = glm::normalize(hit._point - _center);
	hit.setFaceNormal(ray, outwardNormal);

	return true;
}
