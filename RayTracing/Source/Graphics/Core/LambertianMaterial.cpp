#include "stdafx.h"
#include "LambertianMaterial.h"

#include "Graphics/Core/Material.h"
#include "Utilities/ONB.h"

// [Public methods]

bool LambertianMaterial::scatter(Material* material, const Ray3D& ray, const Hittable::HitRecord& record, vec3& attenuation, Ray3D& scattered, float& PDF) const
{
	ONB onb;
	onb.buildFromW(record._normal);
	
	vec3 scatterDirection = onb.localVector(RandomUtilities::getUniformRandomCosineDirection());
	scattered = Ray3D(record._point, glm::normalize(scatterDirection), ray.getTimestamp());
	attenuation = material->_albedoTexture->getColor(record._uv, record._point);
	PDF = glm::dot(onb.w(), scattered.getDirection()) / glm::pi<float>();

	return true;
}

float LambertianMaterial::scatterPDF(const Ray3D& ray, const Hittable::HitRecord& record, Ray3D& scattered)
{
	const float cosine = glm::dot(record._normal, glm::normalize(scattered.getDirection()));
	return cosine < .0f ? .0f : cosine / glm::pi<float>();
}
