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
	std::vector<float>	_random;				//!<

protected:
	/**
	*	@brief  
	*/
	void generatePermutation(int index);

	/**
	*	@brief  
	*/
	static void permute(std::vector<int>& permutation, int size);

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
};

