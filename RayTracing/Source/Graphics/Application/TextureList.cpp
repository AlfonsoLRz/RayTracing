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
	// Solution to increase flexibility of texture instantiation: define here only those textures which doesn't come from images in file system or use different parameters for
	// magnification / mignification or wrapping S / T

	_texture[CGApplicationEnumerations::TEXTURE_BLACK] = std::unique_ptr<Texture>(new Texture(vec4(0.0f, 0.0f, 0.0f, 1.0f)));
	_texture[CGApplicationEnumerations::TEXTURE_BLUE] = std::unique_ptr<Texture>(new Texture(vec4(0.35f, 0.35f, 1.0f, 1.0f)));
	_texture[CGApplicationEnumerations::TEXTURE_GRAY_64] = std::unique_ptr<Texture>(new Texture(vec4(0.25f, 0.25f, 0.25f, 1.0f)));
	_texture[CGApplicationEnumerations::TEXTURE_GRAY_127] = std::unique_ptr<Texture>(new Texture(vec4(0.5f, 0.5f, 0.5f, 1.0f)));
	_texture[CGApplicationEnumerations::TEXTURE_GRAY_192] = std::unique_ptr<Texture>(new Texture(vec4(0.75f, 0.75f, 0.75f, 1.0f)));
	_texture[CGApplicationEnumerations::TEXTURE_GREEN] = std::unique_ptr<Texture>(new Texture(vec4(0.0f, 1.0f, 0.0f, 1.0f)));
	_texture[CGApplicationEnumerations::TEXTURE_RED] = std::unique_ptr<Texture>(new Texture(vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	_texture[CGApplicationEnumerations::TEXTURE_WHITE] = std::unique_ptr<Texture>(new Texture(vec4(1.0f, 1.0f, 1.0f, 1.0f)));
	_texture[CGApplicationEnumerations::TEXTURE_YELLOW] = std::unique_ptr<Texture>(new Texture(vec4(1.0f, 1.0f, 0.0f, 1.0f)));
}

/// [Public methods]

Texture* TextureList::getTexture(const CGApplicationEnumerations::TextureNames texture)
{
	if (!_texture[texture].get())
	{
		if (TEXTURE_PATH.find(texture) == TEXTURE_PATH.end())
		{
			return nullptr;
		}

		const std::string texturePath = TEXTURE_PATH[texture];
		UnsignedImage* image = new UnsignedImage(texturePath);
		Texture* pTexture = new Texture(image);

		_texture[texture].reset(pTexture);
		delete image;
	}

	return _texture[texture].get();
}
