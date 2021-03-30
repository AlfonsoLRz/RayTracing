#include "stdafx.h"
#include "MaterialList.h"

#include "Graphics/Application/TextureList.h"

/// [Protected methods]

MaterialList::MaterialList()
	: _material(CGApplicationEnumerations::numAvailableMaterials()), _materialSpecs(CGApplicationEnumerations::numAvailableMaterials())
{
	this->defineMaterials();
}

void MaterialList::createMaterial(const CGApplicationEnumerations::MaterialNames material)
{
	Material* pMaterial = new Material();

	for (int i = 0; i < Texture::NUM_TEXTURE_TYPES; ++i)
	{
		if (_materialSpecs[material]._texture[i] != -1)
		{
			pMaterial->setTexture(static_cast<Texture::TextureTypes>(i), TextureList::getInstance()->getTexture(static_cast<CGApplicationEnumerations::TextureNames>(_materialSpecs[material]._texture[i])));
		}
	}

	pMaterial->setShininess(_materialSpecs[material]._shininess);

	_material[material].reset(pMaterial);
}

void MaterialList::defineMaterials()
{
	_materialSpecs[CGApplicationEnumerations::MATERIAL_CAD_WHITE]._texture[Texture::KAD_TEXTURE] = CGApplicationEnumerations::TEXTURE_WHITE;
	_materialSpecs[CGApplicationEnumerations::MATERIAL_CAD_WHITE]._texture[Texture::KS_TEXTURE] = CGApplicationEnumerations::TEXTURE_BLACK;
	_materialSpecs[CGApplicationEnumerations::MATERIAL_CAD_WHITE]._shininess = 100.0f;
}

/// [Public methods]

Material* MaterialList::getMaterial(const CGApplicationEnumerations::MaterialNames material)
{
	if (!_material[material].get())
	{
		this->createMaterial(material);
	}

	return _material[material].get();
}
