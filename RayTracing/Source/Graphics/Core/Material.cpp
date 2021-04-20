#include "stdafx.h"
#include "Material.h"

#include "Graphics/Core/LambertianMaterial.h"
#include "Graphics/Core/MaterialType.h"
#include "Graphics/Core/MetalMaterial.h"

// [Static members initialization]

const MaterialTypeVector Material::MATERIAL_APPLICATOR = Material::buildMaterialApplicators();

/// [Public methods]

Material::Material(const vec3& albedo)
	: _albedo(albedo), _shininess(1.0f), _materialType(MaterialType::LAMBERTIAN)
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

void Material::setShininess(const float shininess)
{
	_shininess = shininess;
}

void Material::setTexture(const Texture::TextureTypes textureType, Texture* texture)
{
	_texture[textureType] = texture;
}

/// [Protected methods]

MaterialTypeVector Material::buildMaterialApplicators()
{
	MaterialTypeVector materialApplicators(MaterialType::NUM_MATERIAL_TYPES);

	materialApplicators[MaterialType::LAMBERTIAN].reset(new LambertianMaterial());
	materialApplicators[MaterialType::METAL].reset(new MetalMaterial());

	return materialApplicators;
}

void Material::copyAttributes(const Material& material)
{
	this->_albedo = material._albedo;
	this->_materialType = material._materialType;
	
	memcpy(&_texture, &material._texture, sizeof(material._texture));
	this->_shininess = material._shininess;
}
