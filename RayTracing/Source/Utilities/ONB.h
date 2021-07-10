#pragma once

/**
*	@file ONB.h
*	@authors Alfonso L�pez Ruiz (alr00048@red.ujaen.es)
*	@date 04/07/2021
*/

/**
*	@brief 
*/
class ONB
{
protected:
	vec3 _axis[3];			//!<

public:
	/**
	*	@brief Builds the orthonormal basis from w. 
	*/
	void buildFromW(const vec3& w);

	/**
	*	@brief Translates any vector to orthonormal basis system.
	*/
	vec3 localVector(const vec3& vector) const;

	// --------- Getters -----------

	/**
	*	@return X vector of ONB system.  
	*/
	vec3 u() const { return _axis[0]; }

	/**
	*	@return Y vector of ONB system.
	*/
	vec3 v() const { return _axis[1]; }

	/**
	*	@return Z vector of ONB system.
	*/
	vec3 w() const { return _axis[2]; }
};

