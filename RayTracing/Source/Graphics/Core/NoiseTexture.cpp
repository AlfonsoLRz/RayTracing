#include "stdafx.h"
#include "NoiseTexture.h"

// [Public methods]

NoiseTexture::NoiseTexture(float frequency) : _frequency(frequency)
{
}

vec3 NoiseTexture::getColor(const vec2& uv, const vec3& point)
{
	return vec3((_perlinNoise.getNoise(point * _frequency) + 1.0f) * .5f);
}
