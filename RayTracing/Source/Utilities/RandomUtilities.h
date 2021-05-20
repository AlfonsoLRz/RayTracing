#pragma once

#include "stdafx.h"

/**
*	@file RandomUtilities.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 17/04/2021
*/

typedef std::mt19937							RandomNumberGenerator;
typedef std::uniform_real_distribution<float>	DoubleUniformDistribution;

/**
*	@brief Set of utilities to retrieve random values.
*	@author Alfonso López Ruiz.
*/
namespace RandomUtilities
{
	/**
	*	@return New random value retrieved from a random uniform distribution.
	*/
	float getUniformRandom();

	/**
	*	@return New random value retrieved from a random uniform distribution. Note that this value is not in [0, 1].
	*/
	float getUniformRandom(float min, float max);

	/**
	*	@brief Generates a random color in [0, 1] by using getUniformRandom function for each channel.
	*/
	vec3 getUniformRandomColor();

	/**
	*	@brief Generates a random color by using getUniformRandom function for each channel.
	*/
	vec3 getUniformRandomColor(float min, float max);

	/**
	*	@return Random point in unit sphere.
	*/
	vec3 getUniformRandomInHemisphere(const vec3& normal);

	/**
	*	@return Random single integer value.
	*/
	int getUniformRandomInt(int min, int max);
	
	/**
	*	@return Random point in unit disk.
	*/
	vec3 getUniformRandomInUnitDisk();

	/**
	*	@return Random point in unit sphere. 
	*/
	vec3 getUniformRandomInUnitSphere();
}

inline float RandomUtilities::getUniformRandom()
{
	static RandomNumberGenerator generator;
	static DoubleUniformDistribution distribution(.0f, 1.0f);

	return distribution(generator);
}

inline float RandomUtilities::getUniformRandom(float min, float max)
{
	return min + (max - min) * getUniformRandom();
}

inline vec3 RandomUtilities::getUniformRandomColor()
{
	return vec3(RandomUtilities::getUniformRandom(), RandomUtilities::getUniformRandom(), RandomUtilities::getUniformRandom());
}
inline vec3 RandomUtilities::getUniformRandomColor(float min, float max)
{
	return vec3(RandomUtilities::getUniformRandom(min, max), RandomUtilities::getUniformRandom(min, max), RandomUtilities::getUniformRandom(min, max));
}

inline vec3 RandomUtilities::getUniformRandomInHemisphere(const vec3& normal)
{
	vec3 unitSphere = getUniformRandomInUnitSphere();

	return unitSphere * -1.0f * ((glm::dot(unitSphere, normal) > .0f) * 2.0f - 1.0f);
}

inline int RandomUtilities::getUniformRandomInt(int min, int max)
{
	return static_cast<int>(getUniformRandom(min, max));
}

inline vec3 RandomUtilities::getUniformRandomInUnitDisk()
{
	while (true)
	{
		vec3 point = vec3(getUniformRandom(-1.0f, 1.0f), getUniformRandom(-1.0f, 1.0f), .0f);
		if (glm::length2(point) >= 1) continue;

		return point;
	}
}

inline vec3 RandomUtilities::getUniformRandomInUnitSphere()
{
	vec3 point;
	while (true)
	{
		point = vec3(getUniformRandom(-1.0f, 1.0f), getUniformRandom(-1.0f, 1.0f), getUniformRandom(-1.0f, 1.0f));
		if (glm::length2(point) >= 1) continue;

		return point;
	}
}
