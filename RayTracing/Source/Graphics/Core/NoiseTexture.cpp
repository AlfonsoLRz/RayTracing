#include "stdafx.h"
#include "NoiseTexture.h"

// [Public methods]

NoiseTexture::NoiseTexture(float frequency, unsigned octaves) : _frequency(frequency), _octaves(octaves)
{
}

vec3 NoiseTexture::getColor(const vec2& uv, const vec3& point)
{
	return vec3(0.5f * (1.0f + std::sin(_frequency * point.z + 10.0f * _perlinNoise.getTurbulence(point, _octaves))));
}
