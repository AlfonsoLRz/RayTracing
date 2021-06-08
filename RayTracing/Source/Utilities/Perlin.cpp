#include "stdafx.h"
#include "Perlin.h"

#include "Utilities/RandomUtilities.h"

// [Static attributes]

const unsigned Perlin::NUM_POINTS = 256;

// [Public methods]

Perlin::Perlin()
{
	_random.resize(NUM_POINTS);
	for (int randomIdx = 0; randomIdx < NUM_POINTS; ++randomIdx)
	{
		_random[randomIdx] = RandomUtilities::getUniformRandom();
	}

	this->generatePermutation(0);
	this->generatePermutation(1);
	this->generatePermutation(2);
}

Perlin::~Perlin()
{
}

float Perlin::getNoise(const vec3& position)
{
	int i = static_cast<int>(4.0f * position.x) & 255;
	int j = static_cast<int>(4.0f * position.y) & 255;
	int k = static_cast<int>(4.0f * position.z) & 255;
	
	return _random[_permutation[0][i] ^ _permutation[1][j] ^ _permutation[2][k]];
}

// [Protected methods]

void Perlin::generatePermutation(int index)
{
	_permutation[index].resize(NUM_POINTS);
	std::iota(_permutation[index].begin(), _permutation[index].end(), 0);

	Perlin::permute(_permutation[index], NUM_POINTS);
}

void Perlin::permute(std::vector<int>& permutation, int size)
{
	for (int idx = size - 1; idx > 0; --idx)
	{
		int target = RandomUtilities::getUniformRandomInt(0, idx);
		std::swap(permutation[idx], permutation[target]);
	}
}