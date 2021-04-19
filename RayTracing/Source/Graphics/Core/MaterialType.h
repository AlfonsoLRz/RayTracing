#pragma once

#include "stdafx.h"
#include "Geometry/3D/Ray3D.h"
#include "Graphics/Core/Hittable.h"
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
	/**
	*	@brief
	*/
	virtual bool scatter(Material* material, const Ray3D& ray, const Hittable::HitRecord& record, vec3& attenuation, Ray3D& scattered) const = 0;
};
