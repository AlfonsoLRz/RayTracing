#pragma once

#include "Graphics/Core/MaterialType.h"

/**
*	@file DiffuseLightMaterial.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 07/06/2021
*/

/**
*	@brief
*/
class DiffuseLightMaterial: public MaterialType
{
public:
	/**
	*	@brief Emission for emissive materials.
	*/
	virtual vec3 emit(Material* material, const vec2& uv, const vec3& point) const;

	/**
	*	@brief
	*/
	virtual bool scatter(Material* material, const Ray3D& ray, const Hittable::HitRecord& record, vec3& attenuation, Ray3D& scattered) const;
};

