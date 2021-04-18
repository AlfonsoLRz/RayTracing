#pragma once

#include "stdafx.h"

/**
*	@file RandomUtilities.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 17/04/2021
*/

typedef std::mt19937_64							RandomNumberGenerator;
typedef std::uniform_real_distribution<double>	DoubleUniformDistribution;

/**
*	@brief Set of utilities to retrieve random values.
*	@author Alfonso López Ruiz.
*/
namespace RandomUtilities
{
	/**
	*	@return New random value retrieved from a random uniform distribution.
	*/
	double getUniformRandom();

	/**
	*	@return New random value retrieved from a random uniform distribution. Note that this value is not in [0, 1].
	*/
	double getUniformRandom(float min, float max);

	/**
	*	@return Random point in unit sphere. 
	*/
	vec3 getUniformRandomInUnitSphere();
}

inline double RandomUtilities::getUniformRandom()
{
	static DoubleUniformDistribution distribution(.0f, 1.0f);
	static RandomNumberGenerator generator;

	return distribution(generator);
}

double RandomUtilities::getUniformRandom(float min, float max)
{
	return min + (max - min) * getUniformRandom();
}

vec3 RandomUtilities::getUniformRandomInUnitSphere()
{
	vec3 point;
	while (true)
	{
		point = vec3(getUniformRandom(-1.0f, 1.0f), getUniformRandom(-1.0f, 1.0f), getUniformRandom(-1.0f, 1.0f));
		if (glm::length2(point) >= 1) continue;

		return point;
	}
}
