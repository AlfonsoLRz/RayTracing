#include "stdafx.h"
#include "MetalMaterial.h"

#include "Graphics/Core/Material.h"

// [Public methods]

bool MetalMaterial::scatter(Material* material, const Ray3D& ray, const Hittable::HitRecord& record, vec3& attenuation, Ray3D& scattered) const
{
	vec3 reflectDirection = glm::reflect(glm::normalize(ray.getDirection()), record._normal);
	scattered = Ray3D(record._point, reflectDirection);
	attenuation = material->_albedo;

	return dot(reflectDirection, record._normal) > .0f;
}
