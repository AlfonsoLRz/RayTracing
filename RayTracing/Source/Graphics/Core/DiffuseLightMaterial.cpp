#include "stdafx.h"
#include "DiffuseLightMaterial.h"

#include "Material.h"

// [Public methods]

vec3 DiffuseLightMaterial::emit(Material* material, const vec2& uv, const vec3& point) const
{
	return material->_emissionTexture->getColor(uv, point);
}

bool DiffuseLightMaterial::scatter(Material* material, const Ray3D& ray, const Hittable::HitRecord& record, vec3& attenuation, Ray3D& scattered) const
{
	return false;
}
