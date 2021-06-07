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
	friend class DielectricMaterial;
	friend class DiffuseLightMaterial;
	friend class LambertianMaterial;
	friend class MetalMaterial;

protected:
	const static MaterialTypeVector MATERIAL_APPLICATOR;		//!< 

protected:
	// [Ray Tracing] 
	std::shared_ptr<Texture>	_albedoTexture;					//!<
	std::shared_ptr<Texture>	_emissionTexture;				//!<
	unsigned					_materialType;					//!< 
	float						_reflectionFuzz;				//!< Reflection noise disturbance
	float						_refractionIndex;				//!< Refraction index

	// [Old Features]
	float						_shininess;						//!< Phong exponent for specular reflection	

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
	*	@brief Default constructor.
	*/
	Material(std::shared_ptr<Texture> albedo);

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

	// ----- Setters ------
	
	/**
	*	@brief  
	*/
	Material* setMaterialType(MaterialType::MaterialTypes type);

	/**
	*	@brief  
	*/
	Material* setReflectionFuzz(const float fuzz);

	/**
	*	@brief  
	*/
	Material* setRefractionIndex(const float refractionIndex);
	
	/**
	*	@brief Modifies the Phong exponent of material.
	*	@param shininess New shininess exponent.
	*/
	Material* setShininess(const float shininess);

	// ----- Getters ------

	/**
	*	@return  
	*/
	MaterialType* getApplicator() { return MATERIAL_APPLICATOR[_materialType].get(); }

public:
	struct MaterialSpecs
	{
		//int16_t _texture[Texture::NUM_TEXTURE_TYPES];
		float _shininess;

		/**
		*	@brief Default constructor.
		*/
		MaterialSpecs()
		{
			//for (int i = 0; i < Texture::NUM_TEXTURE_TYPES; ++i)
			//{
			//	_texture[i] = -1;
			//}

			_shininess = 1.0f;
		}
	};
};

