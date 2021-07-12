#include "stdafx.h"
#include "MetalMaterial.h"

#include "Graphics/Core/Material.h"

// [Public methods]

bool MetalMaterial::scatter(Material* material, const Ray3D& ray, const Hittable::HitRecord& record, ScatterRecord& scatterRecord) const
{
	vec3 reflectDirection		= glm::reflect(glm::normalize(ray.getDirection()), record._normal);
	
	scatterRecord._specularRay	= Ray3D(record._point, reflectDirection + material->_reflectionFuzz * RandomUtilities::getUniformRandomInUnitSphere(), ray.getTimestamp());
	scatterRecord._isSpecular	= true;
	scatterRecord._attenuation	= material->_albedoTexture->getColor(record._uv, record._point);
	scatterRecord._pdf.reset();

	return true;
}

float MetalMaterial::scatterPDF(const Ray3D& ray, const Hittable::HitRecord& record, Ray3D& scattered)
{
	return 0.0f;
}
