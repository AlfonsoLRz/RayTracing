#pragma once

#include "Graphics/Core/MaterialType.h"
#include "Graphics/Core/Texture.h"

/**
*	@file LambertianMaterial.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 19/04/2021
*/

/**
*	@brief 
*/
class LambertianMaterial: public MaterialType
{
public:
	/**
	*	@brief
	*/
	virtual bool scatter(Material* material, const Ray3D& ray, const Hittable::HitRecord& record, vec3& attenuation, Ray3D& scattered, float& PDF) const;

	/**
	*	@brief Scatter non-uniformly based on a PDF distribution.
	*/
	virtual float scatterPDF(const Ray3D& ray, const Hittable::HitRecord& record, Ray3D& scattered);
};

