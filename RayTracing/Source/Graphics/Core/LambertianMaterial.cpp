#include "stdafx.h"
#include "LambertianMaterial.h"

#include "Graphics/Core/Material.h"

// [Public methods]

bool LambertianMaterial::scatter(Material* material, const Ray3D& ray, const Hittable::HitRecord& record, vec3& attenuation, Ray3D& scattered) const
{
	vec3 scatterDirection = record._normal + RandomUtilities::getUniformRandomInUnitSphere();

	if (BasicOperations::isZero(scatterDirection))
	{
		scatterDirection = record._normal;
	}

	scattered = Ray3D(record._point, scatterDirection, ray.getTimestamp());
	attenuation = material->_albedo;

	return true;
}
