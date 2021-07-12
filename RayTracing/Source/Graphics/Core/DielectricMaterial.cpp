#include "stdafx.h"
#include "DielectricMaterial.h"

#include "Material.h"

// [Public methods]

bool DielectricMaterial::scatter(Material* material, const Ray3D& ray, const Hittable::HitRecord& record, ScatterRecord& scatterRecord) const
{
	float refractionRatio = record._frontFace ? 1.0f / material->_refractionIndex : material->_refractionIndex;

	vec3 unitDirection = glm::normalize(ray.getDirection());
	float cosTheta = glm::min(glm::dot(-unitDirection, record._normal), 1.0f);
	float sinTheta = sqrt(1.0f - cosTheta * cosTheta);

	bool cannotRefract = refractionRatio * sinTheta > 1.0f;
	vec3 direction;

	if (cannotRefract || reflectanceSchlick(cosTheta, refractionRatio) > RandomUtilities::getUniformRandom())
	{
		direction = glm::reflect(unitDirection, record._normal);
	}
	else
	{
		direction = glm::refract(unitDirection, record._normal, refractionRatio);
	}

	scatterRecord._isSpecular	= true;
	scatterRecord._attenuation	= vec3(1.0f);
	scatterRecord._specularRay	= Ray3D(record._point, direction, ray.getTimestamp());
	scatterRecord._pdf.reset();

	return true;
}

float DielectricMaterial::scatterPDF(const Ray3D& ray, const Hittable::HitRecord& record, Ray3D& scattered)
{
	return 0.0f;
}

// [Protected methods]

float DielectricMaterial::reflectanceSchlick(float cosine, float refIdx) const 
{
	float r0 = (1.0f - refIdx) / (1.0f + refIdx);
	r0 *= r0;

	return r0 + (1.0f - r0) * pow(1.0f - cosine, 5.0f);
}