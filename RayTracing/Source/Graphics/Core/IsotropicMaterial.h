#pragma once

/**
*	@file IsotropicMaterial.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 21/06/2021
*/

#include "Graphics/Core/MaterialType.h"
#include "Graphics/Core/Texture.h"

/**
*	@brief
*/
class IsotropicMaterial: public MaterialType
{
public:
	/**
	*	@brief
	*/
	virtual bool scatter(Material* material, const Ray3D& ray, const Hittable::HitRecord& record, vec3& attenuation, Ray3D& scattered) const;
};

