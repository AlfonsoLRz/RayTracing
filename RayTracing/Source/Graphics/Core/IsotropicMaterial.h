#pragma once

/**
*	@file IsotropicMaterial.h
*	@authors Alfonso L�pez Ruiz (alr00048@red.ujaen.es)
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
	virtual bool scatter(Material* material, const Ray3D& ray, const Hittable::HitRecord& record, ScatterRecord& scatterRecord) const;

	/**
	*	@brief Scatter non-uniformly based on a PDF distribution.
	*/
	virtual float scatterPDF(const Ray3D& ray, const Hittable::HitRecord& record, Ray3D& scattered);
};

