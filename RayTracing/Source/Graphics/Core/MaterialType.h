#pragma once

#include "stdafx.h"
#include "Geometry/3D/Ray3D.h"
#include "Graphics/Core/Hittable.h"
#include "Graphics/Core/PDF.h"
#include "Utilities/BasicOperations.h"
#include "Utilities/RandomUtilities.h"

/**
*	@file MaterialType.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 19/04/2021
*/

class Material;

/**
*	@brief --
*/
class MaterialType
{
public:
	struct ScatterRecord
	{
		vec3					_attenuation;
		bool					_isSpecular;
		std::shared_ptr<PDF>	_pdf;
		Ray3D					_specularRay;
	};

public:
	enum MaterialTypes { LAMBERTIAN, METAL, DIELECTRIC, DIFFUSE_LIGHT, ISOTROPIC, NUM_MATERIAL_TYPES };

public:
	/**
	*	@brief Emission for emissive materials. 
	*/
	virtual vec3 emit(Material* material, const Hittable::HitRecord& record, const vec2& uv, const vec3& point) const;
	
	/**
	*	@brief
	*/
	virtual bool scatter(Material* material, const Ray3D& ray, const Hittable::HitRecord& record, ScatterRecord& scatterRecord) const = 0;

	/**
	*	@brief Scatter non-uniformly based on a PDF distribution.
	*/
	virtual float scatterPDF(const Ray3D& ray, const Hittable::HitRecord& record, Ray3D& scattered);
};
