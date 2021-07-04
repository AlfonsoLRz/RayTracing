#include "stdafx.h"
#include "ONB.h"

// [Public methods]

void ONB::buildFromW(const vec3& w)
{
	_axis[2] = glm::normalize(w);

	vec3 up = std::fabs(this->w().x) > .9f ? vec3(.0f, 1.0f, .0f) : vec3(1.0f, .0f, .0f);
	_axis[1] = glm::normalize(glm::cross(this->w(), up));
	_axis[0] = glm::normalize(glm::cross(this->w(), this->v()));
}

vec3 ONB::localVector(const vec3& v)
{
	return v.x * _axis[0] + v.y * _axis[1] + v.z * _axis[2];
}
