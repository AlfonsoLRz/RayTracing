#pragma once

/**
*	@file Texture.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 07/18/2019
*/

/**
*	@brief Wraps an image which takes part in a material.
*/
class Ray3D
{
protected:
	vec3	_origin, _direction;		//!< Variables for ray equation
	float	_time;						//!< Timestamp when ray was launched

public:
	/**
	*	@brief Default constructor for a ray. 
	*/
	Ray3D(const vec3& origin, const vec3& direction, float timestamp = .0f);

	/**
	*	@brief Point at parametric value t for ray equation.
	*/
	vec3 at(const float t) const;

	// ------- Getters ---------

	/**
	*	@return Origin of ray. 
	*/
	vec3 getOrigin() const { return _origin; }

	/**
	*	@return Direction of ray. 
	*/
	vec3 getDirection() const { return _direction; }

	/**
	*	@return Timestamp at when the ray was launched. 
	*/
	float getTimestamp() const { return _time; }
};

