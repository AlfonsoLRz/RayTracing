#include "stdafx.h"
#include "DiffuseLightMaterial.h"

#include "Material.h"

// [Public methods]

vec3 DiffuseLightMaterial::emit(Material* material, const Hittable::HitRecord& record, const vec2& uv, const vec3& point) const
{
	if (record._frontFace)
		return material->_emissionTexture->getColor(uv, point);

	return vec3(.0f);
}

bool DiffuseLightMaterial::scatter(Material* material, const Ray3D& ray, const Hittable::HitRecord& record, vec3& attenuation, Ray3D& scattered, float& PDF) const
{
	return false;
}

float DiffuseLightMaterial::scatterPDF(const Ray3D& ray, const Hittable::HitRecord& record, Ray3D& scattered)
{
	return 0.0f;
}
