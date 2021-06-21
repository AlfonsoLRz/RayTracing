#include "stdafx.h"
#include "ConstantMedium.h"

#include "Material.h"

// [Public methods]

ConstantMedium::ConstantMedium(std::shared_ptr<Hittable> boundary, std::shared_ptr<Texture> albedo, double density) :
	_boundary(boundary), _negativeInverseDensity(-1.0f / density), _phaseFunction(std::make_shared<Material>(albedo))
{
	_phaseFunction->setMaterialType(MaterialType::ISOTROPIC);
}

ConstantMedium::ConstantMedium(std::shared_ptr<Hittable> boundary, const vec3& color, double density) :
	_boundary(boundary), _negativeInverseDensity(-1.0f / density), _phaseFunction(std::make_shared<Material>(color))
{
	_phaseFunction->setMaterialType(MaterialType::ISOTROPIC);
}

bool ConstantMedium::getBoundingBox(float time0, float time1, AABB& aabb) const
{
	return _boundary->getBoundingBox(time0, time1, aabb); 
}

bool ConstantMedium::hit(const Ray3D& ray, double tMin, double tMax, HitRecord& hit) const
{
	HitRecord r1, r2;

	if (!_boundary->hit(ray, -FLT_MAX, FLT_MAX, r1))
	{
		return false;
	}

	if (!_boundary->hit(ray, r1._t + .0001f, FLT_MAX, r2))
	{
		return false;
	}

	if (r1._t < tMin) r1._t = tMin;
	if (r2._t > tMax) r2._t = tMax;
	if (r1._t >= r2._t) return false;
	r1._t = glm::clamp(r1._t, .0f, FLT_MAX);

	const float rayLength		= ray.getDirection().length();
	const float distanceInside	= (r2._t - r1._t) * rayLength;
	const float hitDistance		= _negativeInverseDensity * std::log(RandomUtilities::getUniformRandom());

	if (hitDistance > distanceInside) return false;

	hit._t			= r1._t + hitDistance / rayLength;
	hit._point		= ray.at(hit._t);
	hit._normal		= vec3(1.0f, .0f, .0f);
	hit._frontFace	= true;
	hit._material	= _phaseFunction;

	return true;
}
