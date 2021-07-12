#include "stdafx.h"
#include "IsotropicMaterial.h"

#include "Material.h"

// [Public methods]

bool IsotropicMaterial::scatter(Material* material, const Ray3D& ray, const Hittable::HitRecord& record, ScatterRecord& scatterRecord) const
{
	//scatterRecord.scattered = Ray3D(record._point, RandomUtilities::getUniformRandomInUnitSphere(), ray.getTimestamp());
	scatterRecord._attenuation = material->_albedoTexture->getColor(record._uv, record._point);

	return true;
}

float IsotropicMaterial::scatterPDF(const Ray3D& ray, const Hittable::HitRecord& record, Ray3D& scattered)
{
	return 0.0f;
}
