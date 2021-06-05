#include "stdafx.h"
#include "TextureList.h"

#include "Graphics/Core/UnsignedImage.h"

// [Static members initialization]

std::unordered_map<uint16_t, std::string> TextureList::TEXTURE_PATH
{
	//{CGAppEnum::TEXTURE_CLAY_ALBEDO, "Assets/Textures/Floor/Clay/Albedo.png"},
};

/// [Protected methods]

TextureList::TextureList()
	: _texture(CGApplicationEnumerations::numAvailableTextures())
{
	this->loadTextures();
}

void TextureList::loadTextures()
{
}

/// [Public methods]

Texture* TextureList::getTexture(const CGApplicationEnumerations::TextureNames texture)
{
	return nullptr;
}
