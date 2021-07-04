#include "stdafx.h"
#include "Hittable.h"

#include "Graphics/Core/Material.h"

// [Hittable]

Hittable::Hittable() : _flipNormals(false)
{
}

Hittable::Hittable(std::shared_ptr<Material> material)
{
	this->_material = material;
}

// [Protected methods]

void Hittable::flipRecordNormals(HitRecord& record) const
{
	record._frontFace = _flipNormals ^ record._frontFace;			// XOR to modify frontFace only when flipNormals = true
}

// [Hit record]

void Hittable::HitRecord::setFaceNormal(const Ray3D& ray, const vec3& outwardNormal)
{
	_frontFace = glm::dot(ray.getDirection(), outwardNormal) < .0f;
	_normal = _frontFace ? outwardNormal : -outwardNormal;
}