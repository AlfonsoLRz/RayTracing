#include "stdafx.h"
#include "Ray3D.h"

// [Public methods]

Ray3D::Ray3D(const vec3& origin, const vec3& direction, float timestamp) :
	_origin(origin), _direction(direction), _time(timestamp)
{
}

vec3 Ray3D::at(const float t) const
{
	return _origin + t * _direction;
}
