#include "stdafx.h"
#include "MaterialType.h"

#include "Material.h"

// [Public methods]

vec3 MaterialType::emit(Material* material, const Hittable::HitRecord& record, const vec2& uv, const vec3& point) const
{
    return vec3(.0f);
}

float MaterialType::scatterPDF(const Ray3D& ray, const Hittable::HitRecord& record, Ray3D& scattered)
{
    return 0.0f;
}
