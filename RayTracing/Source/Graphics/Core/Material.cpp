#include "stdafx.h"
#include "Material.h"

#include "Graphics/Core/DielectricMaterial.h"
#include "Graphics/Core/LambertianMaterial.h"
#include "Graphics/Core/MaterialType.h"
#include "Graphics/Core/MetalMaterial.h"

// [Static members initialization]

const MaterialTypeVector Material::MATERIAL_APPLICATOR = Material::buildMaterialApplicators();

/// [Public methods]

Material::Material(const vec3& albedo)
	: _albedo(albedo), _shininess(1.0f), _materialType(MaterialType::LAMBERTIAN), _reflectionFuzz(.0f), _refractionIndex(1.5f)
{
	for (int i = 0; i < Texture::NUM_TEXTURE_TYPES; ++i)
	{
		_texture[i] = nullptr;
	}
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

void Material::applyMaterial(RenderingShader* shader)
{
	if (_texture[Texture::KAD_TEXTURE])
	{
		_texture[Texture::KAD_TEXTURE]->applyTexture(shader, Texture::KAD_TEXTURE);
	}

	if (_texture[Texture::KS_TEXTURE])
	{
		shader->setUniform("shininess", _shininess);

		_texture[Texture::KS_TEXTURE]->applyTexture(shader, Texture::KS_TEXTURE);
	}

	if (_texture[Texture::SEMI_TRANSPARENT_TEXTURE])
	{
		shader->setSubroutineUniform(GL_FRAGMENT_SHADER, "semiTransparentUniform", "semiTransparentTexture");

		_texture[Texture::SEMI_TRANSPARENT_TEXTURE]->applyTexture(shader, Texture::SEMI_TRANSPARENT_TEXTURE);
	}
	else
	{
		shader->setSubroutineUniform(GL_FRAGMENT_SHADER, "semiTransparentUniform", "noSemiTransparentTexture");
	}

	shader->applyActiveSubroutines();
}

void Material::applyTexture(ShaderProgram* shader, const Texture::TextureTypes textureType)
{
	if (_texture[textureType])
	{
		_texture[textureType]->applyTexture(shader, textureType);
	}
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

Material* Material::setTexture(const Texture::TextureTypes textureType, Texture* texture)
{
	_texture[textureType] = texture;

	return this;
}

/// [Protected methods]

MaterialTypeVector Material::buildMaterialApplicators()
{
	MaterialTypeVector materialApplicators(MaterialType::NUM_MATERIAL_TYPES);

	materialApplicators[MaterialType::LAMBERTIAN].reset(new LambertianMaterial());
	materialApplicators[MaterialType::METAL].reset(new MetalMaterial());
	materialApplicators[MaterialType::DIELECTRIC].reset(new DielectricMaterial());

	return materialApplicators;
}

void Material::copyAttributes(const Material& material)
{
	this->_albedo = material._albedo;
	this->_materialType = material._materialType;
	
	memcpy(&_texture, &material._texture, sizeof(material._texture));
	this->_shininess = material._shininess;
}
