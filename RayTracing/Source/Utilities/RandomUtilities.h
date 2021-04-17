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
}

inline double RandomUtilities::getUniformRandom()
{
	static DoubleUniformDistribution distribution(.0f, 1.0f);
	static RandomNumberGenerator generator;

	return distribution(generator);
}