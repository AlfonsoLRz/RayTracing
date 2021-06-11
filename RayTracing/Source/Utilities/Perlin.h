#pragma once

/**
*	@file Perlin.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 07/26/2019
*/

/**
*	@brief Perlin noise function.
*/
class Perlin
{
protected:
	static const unsigned NUM_POINTS;			//!< Permutation size

protected:
	std::vector<int>	_permutation[3];		//!<
	std::vector<vec3>	_random;				//!<

protected:
	/**
	*	@brief  
	*/
	void generatePermutation(int index);

	/**
	*	@brief  
	*/
	static void permute(std::vector<int>& permutation, int size);

	/**
	*	@brief  
	*/
	static float trilinearInterpolation(vec3 c[2][2][2], float u, float v, float w);

public:
	/**
	*	@brief Default constructor. 
	*/
	Perlin();

	/**
	*	@brief Destructor. 
	*/
	~Perlin();

	/**
	*	@return Noise value for a three-dimensional position. 
	*/
	float getNoise(const vec3& position);

	/**
	*	@brief Add octaves to noise value.
	*/
	float getTurbulence(const vec3& position, unsigned depth = 7);
};

