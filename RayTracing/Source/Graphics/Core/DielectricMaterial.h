#pragma once

#include "Graphics/Core/MaterialType.h"

/**
*	@file DielectricMaterial.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 04/05/2021
*/

/**
*	@brief
*/
class DielectricMaterial: public MaterialType
{
protected:
	/**
	*	@brief  
	*/
	float reflectanceSchlick(float cosine, float refIdx) const;

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

