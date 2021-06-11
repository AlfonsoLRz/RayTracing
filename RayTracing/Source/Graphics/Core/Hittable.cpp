#include "stdafx.h"
#include "Hittable.h"

#include "Graphics/Core/Material.h"

// [Hittable]

Hittable::Hittable()
{
}

Hittable::Hittable(std::shared_ptr<Material> material)
{
	this->_material = material;
}

// [Hit record]

void Hittable::HitRecord::setFaceNormal(const Ray3D& ray, const vec3& outwardNormal)
{
	_frontFace = glm::dot(ray.getDirection(), outwardNormal) < .0f;
	_normal = _frontFace ? outwardNormal : -outwardNormal;
}