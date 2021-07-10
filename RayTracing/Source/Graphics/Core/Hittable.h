#pragma once

#include "Geometry/3D/AABB.h"
#include "Geometry/3D/Ray3D.h"

/**
*	@file Hittable.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 15/04/2021
*/

class Material;

/**
*	@brief---
*/
class Hittable
{
public:
	struct HitRecord
	{
		bool						_frontFace;		//!<
		std::shared_ptr<Material>	_material;		//!<
		vec3						_normal;		//!<
		vec3						_point;			//!<
		float						_t;				//!<
		vec2						_uv;			//!< Texture coordinates

		/**
		*	@brief  
		*/
		void setFaceNormal(const Ray3D& ray, const vec3& outwardNormal);
	};

protected:
	bool						_flipNormals;		//!<
	std::shared_ptr<Material>	_material;			//!<

protected:
	/**
	*	@brief Flips normal of record whether the hittable object is set to.
	*/
	void flipRecordNormals(HitRecord& record) const;

public:
	/**
	*	@brief Default constructor. 
	*/
	Hittable();
	
	/**
	*	@brief Constructor of any hittable object through a material. 
	*/
	Hittable(std::shared_ptr<Material> material);

	/**
	*	@brief Flips normal while calculating hit record.
	*/
	Hittable* flipNormals() { _flipNormals = !_flipNormals; return this; }
	
	/**
	*	@brief
	*/
	virtual bool getBoundingBox(float time0, float time1, AABB& aabb) const = 0;
	
	/**
	*	@brief  
	*/
	virtual bool hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const = 0;

	/**
	*	@return PDF over the surface. 
	*/
	virtual float pdfValue(const vec3& origin, const vec3& direction) const { return .0f; }

	/**
	*	@return Outgoing direction from the origin of a surface. 
	*/
	virtual vec3 random(const vec3& origin) const { return vec3(1.0f, .0f, .0f); };
};

