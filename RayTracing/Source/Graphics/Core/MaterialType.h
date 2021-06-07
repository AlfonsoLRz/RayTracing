#pragma once

#include "stdafx.h"
#include "Geometry/3D/Ray3D.h"
#include "Graphics/Core/Hittable.h"
#include "Utilities/BasicOperations.h"
#include "Utilities/RandomUtilities.h"

/**
*	@file MaterialType.h
*	@authors Alfonso L�pez Ruiz (alr00048@red.ujaen.es)
*	@date 19/04/2021
*/

class Material;

/**
*	@brief --
*/
class MaterialType
{
public:
	enum MaterialTypes { LAMBERTIAN, METAL, DIELECTRIC, DIFFUSE_LIGHT, NUM_MATERIAL_TYPES };

public:
	/**
	*	@brief Emission for emissive materials. 
	*/
	virtual vec3 emit(Material* material, const vec2& uv, const vec3& point) const;
	
	/**
	*	@brief
	*/
	virtual bool scatter(Material* material, const Ray3D& ray, const Hittable::HitRecord& record, vec3& attenuation, Ray3D& scattered) const = 0;
};
