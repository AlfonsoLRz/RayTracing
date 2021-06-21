#include "stdafx.h"
#include "Material.h"

#include "Graphics/Core/DielectricMaterial.h"
#include "Graphics/Core/DiffuseLightMaterial.h"
#include "Graphics/Core/LambertianMaterial.h"
#include "Graphics/Core/IsotropicMaterial.h"
#include "Graphics/Core/MaterialType.h"
#include "Graphics/Core/MetalMaterial.h"

// [Static members initialization]

const MaterialTypeVector Material::MATERIAL_APPLICATOR = Material::buildMaterialApplicators();

/// [Public methods]

Material::Material(const vec3& albedo)
	: _shininess(1.0f), _materialType(MaterialType::LAMBERTIAN),
	  _reflectionFuzz(.0f), _refractionIndex(1.5f)
{
	_albedoTexture.reset(new SolidColor(albedo));
}

Material::Material(std::shared_ptr<Texture> albedo) :
	_albedoTexture(albedo), _shininess(1.0f), _materialType(MaterialType::LAMBERTIAN),
	_reflectionFuzz(.0f), _refractionIndex(1.5f)
{
}

Material::Material(const Material& material)
{
	this->copyAttributes(material);
}

Material& Material::operator=(const Material& material)
{
	this->copyAttributes(material);

	return *this;
}

Material* Material::setEmissionTexture(const vec3& color)
{
	_emissionTexture.reset(new SolidColor(color));
	
	return this;
}

Material* Material::setMaterialType(MaterialType::MaterialTypes type)
{
	_materialType = type;

	return this;
}

Material* Material::setReflectionFuzz(const float fuzz)
{
	_reflectionFuzz = fuzz < 1 ? fuzz : 1.0f;

	return this;
}

Material* Material::setRefractionIndex(const float refractionIndex)
{
	_refractionIndex = refractionIndex;
	
	return this;
}

Material* Material::setShininess(const float shininess)
{
	_shininess = shininess;

	return this;
}

/// [Protected methods]

MaterialTypeVector Material::buildMaterialApplicators()
{
	MaterialTypeVector materialApplicators(MaterialType::NUM_MATERIAL_TYPES);

	materialApplicators[MaterialType::LAMBERTIAN].reset(new LambertianMaterial());
	materialApplicators[MaterialType::METAL].reset(new MetalMaterial());
	materialApplicators[MaterialType::DIELECTRIC].reset(new DielectricMaterial());
	materialApplicators[MaterialType::DIFFUSE_LIGHT].reset(new DiffuseLightMaterial());
	materialApplicators[MaterialType::ISOTROPIC].reset(new IsotropicMaterial());

	return materialApplicators;
}

void Material::copyAttributes(const Material& material)
{
	this->_albedoTexture = material._albedoTexture;
	this->_materialType = material._materialType;
	
	//memcpy(&_texture, &material._texture, sizeof(material._texture));
	this->_shininess = material._shininess;
}
