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
		_random[randomIdx] = vec3(RandomUtilities::getUniformRandom(-1.0f, 1.0f), RandomUtilities::getUniformRandom(-1.0f, 1.0f), RandomUtilities::getUniformRandom(-1.0f, 1.0f));
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
	vec3 c[2][2][2];
	
	float u = position.x - std::floor(position.x);
	float v = position.y - std::floor(position.y);
	float w = position.z - std::floor(position.z);
	
	int i = static_cast<int>(std::floor(position.x));
	int j = static_cast<int>(std::floor(position.y));
	int k = static_cast<int>(std::floor(position.z));

	for (int di = 0; di < 2; ++di)
	{
		for (int dj = 0; dj < 2; ++dj)
		{
			for (int dk = 0; dk < 2; ++dk)
			{
				c[di][dj][dk] = _random[_permutation[0][(i + di) & 255] ^ _permutation[1][(j + dj) & 255] ^ _permutation[2][(k + dk) & 255]];
			}
		}
	}

	return trilinearInterpolation(c, u, v, w);
}

float Perlin::getTurbulence(const vec3& position, unsigned depth)
{
	float accumulate = .0f, weight = 1.0f;
	vec3 tempPosition = position;

	for (int octave = 0; octave < depth; ++octave)
	{
		accumulate += weight * getNoise(tempPosition);
		weight *= .5f;
		tempPosition *= 2.0f;
	}

	return std::abs(accumulate);
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

float Perlin::trilinearInterpolation(vec3 c[2][2][2], float u, float v, float w)
{
	float accumulation = .0f;

	float hermiteu = u * u * (3.0f - 2.0f * u);
	float hermitev = v * v * (3.0f - 2.0f * v);
	float hermitew = w * w * (3.0f - 2.0f * w);

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				vec3 weightv(u - i, v - j, w - k);
				accumulation += (i * hermiteu + (1 - i) * (1 - hermiteu)) * (j * hermitev + (1 - j) * (1 - hermitev)) * (k * hermitew + (1 - k) * (1 - hermitew)) * dot(c[i][j][k], weightv);
			}
		}
	}

	return accumulation;
}
