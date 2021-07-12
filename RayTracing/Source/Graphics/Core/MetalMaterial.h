#pragma once

#include "Graphics/Core/MaterialType.h"

/**
*	@file MetalMaterial.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
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
	virtual bool scatter(Material* material, const Ray3D& ray, const Hittable::HitRecord& record, ScatterRecord& scatterRecord) const;

	/**
	*	@brief Scatter non-uniformly based on a PDF distribution.
	*/
	virtual float scatterPDF(const Ray3D& ray, const Hittable::HitRecord& record, Ray3D& scattered);
};

