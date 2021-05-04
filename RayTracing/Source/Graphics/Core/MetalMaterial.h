#pragma once

#include "Graphics/Core/MaterialType.h"

/**
*	@file MetalMaterial.h
*	@authors Alfonso L�pez Ruiz (alr00048@red.ujaen.es)
*	@date 20/04/2021
*/

/**
*	@brief 
*/
class MetalMaterial : public MaterialType
{
public:
	/**
	*	@brief
	*/
	virtual bool scatter(Material* material, const Ray3D& ray, const Hittable::HitRecord& record, vec3& attenuation, Ray3D& scattered) const;
};
