#pragma once

#include "Graphics/Core/CGEnumerations.h"
#include "Graphics/Core/ComputeShader.h"
#include "Graphics/Core/MaterialType.h"
#include "Graphics/Core/RenderingShader.h"
#include "Graphics/Core/Texture.h"

/**
*	@file Material.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 07/19/2019
*/

typedef std::vector<std::unique_ptr<MaterialType>> MaterialTypeVector;

/**
*	@brief Set of textures which defines the appearance of an object.
*/
class Material
{
	friend class MaterialType;
	friend class LambertianMaterial;
	friend class MetalMaterial;

protected:
	const static MaterialTypeVector MATERIAL_APPLICATOR;					//!< 

protected:
	// [Ray Tracing]
	vec3		_albedo;
	unsigned	_materialType;

	// [Old Features]
	Texture*	_texture[Texture::NUM_TEXTURE_TYPES];						//!< Texture pointer for each type. Noone of them should exclude others
	float		_shininess;													//!< Phong exponent for specular reflection	

protected:
	/**
	*	@brief Builds an array of pointers to material applicators. 
	*/
	static MaterialTypeVector buildMaterialApplicators();
	
	/**
	*	@brief Copies the members of a material from this one.
	*	@param material Material source.
	*/
	void copyAttributes(const Material& material);

public:
	/**
	*	@brief Default constructor.
	*/
	Material(const vec3& albedo = vec3(.0f));

	/**
	*	@brief Copy constructor.
	*	@param material Parameters source.
	*/
	Material(const Material& material);

	/**
	*	@brief Assignment operator overriding.
	*	@param material Parameters source.
	*/
	Material& operator=(const Material& material);

	/**
	*	@brief Specifies the values of uniform variables from the shader.
	*	@param shader Destiny of values to be specified.
	*/
	void applyMaterial(RenderingShader* shader);

	/**
	*	@brief Applies individual textures. 
	*/
	void applyTexture(ShaderProgram* shader, const Texture::TextureTypes textureType);

	// ----- Setters ------
	
	/**
	*	@brief  
	*/
	void setMaterialType(MaterialType::MaterialTypes type) { _materialType = type; }
	
	/**
	*	@brief Modifies the Phong exponent of material.
	*	@param shininess New shininess exponent.
	*/
	void setShininess(const float shininess);

	/**
	*	@brief Modifies the texture pointer for a certain type.
	*	@param textureType Texture slot.
	*	@param texture New texture.
	*/
	void setTexture(const Texture::TextureTypes textureType, Texture* texture);

	// ----- Getters ------

	/**
	*	@return  
	*/
	MaterialType* getApplicator() { return MATERIAL_APPLICATOR[_materialType].get(); }

public:
	struct MaterialSpecs
	{
		int16_t _texture[Texture::NUM_TEXTURE_TYPES];
		float _shininess;

		/**
		*	@brief Default constructor.
		*/
		MaterialSpecs()
		{
			for (int i = 0; i < Texture::NUM_TEXTURE_TYPES; ++i)
			{
				_texture[i] = -1;
			}

			_shininess = 1.0f;
		}
	};
};

