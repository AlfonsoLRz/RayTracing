#include "stdafx.h"
#include "LambertianMaterial.h"

#include "Graphics/Core/Material.h"
#include "Utilities/ONB.h"

// [Public methods]

bool LambertianMaterial::scatter(Material* material, const Ray3D& ray, const Hittable::HitRecord& record, ScatterRecord& scatterRecord) const
{
	scatterRecord._isSpecular = false;
	scatterRecord._attenuation = material->_albedoTexture->getColor(record._uv, record._point);
	scatterRecord._pdf = std::make_shared<CosinePDF>(record._normal);

	return true;
}

float LambertianMaterial::scatterPDF(const Ray3D& ray, const Hittable::HitRecord& record, Ray3D& scattered)
{
	const float cosine = glm::dot(record._normal, glm::normalize(scattered.getDirection()));
	return cosine < .0f ? .0f : cosine / glm::pi<float>();
}
