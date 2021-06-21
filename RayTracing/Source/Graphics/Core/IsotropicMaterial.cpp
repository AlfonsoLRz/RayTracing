#include "stdafx.h"
#include "IsotropicMaterial.h"

#include "Material.h"

// [Public methods]

bool IsotropicMaterial::scatter(Material* material, const Ray3D& ray, const Hittable::HitRecord& record, vec3& attenuation, Ray3D& scattered) const
{
	scattered = Ray3D(record._point, RandomUtilities::getUniformRandomInUnitSphere(), ray.getTimestamp());
	attenuation = material->_albedoTexture->getColor(record._uv, record._point);

	return true;
}
