#pragma once

#include "Graphics/Core/ComputeShader.h"
#include "Graphics/Core/UnsignedImage.h"
#include "Graphics/Core/ShaderProgram.h"

/**
*	@file OpenGLTexture.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 07/18/2019
*/

/**
*	@brief Wraps an image which takes part in a material.
*/
class OpenGLTexture
{
public:
	enum TextureTypes : uint16_t
	{
		CUBEMAP_TEXTURE,
		KAD_TEXTURE,
		KS_TEXTURE,
		SEMI_TRANSPARENT_TEXTURE,

		NUM_TEXTURE_TYPES
	};

protected:
	// Defaults values
	const static GLuint MAG_FILTER;			//!<
	const static GLuint MIN_FILTER;			//!<
	const static GLuint WRAP_S;				//!<
	const static GLuint WRAP_T;				//!<
	const static GLuint WRAP_R;				//!< Cube map

	const static std::unordered_map<uint16_t, std::string> SHADER_VARIABLE;		//!< Name of each variable related to a texture in a shader, so we can apply uniforms

protected:
	// [OpenGL parameters]
	GLuint	_id;						//!< Texture identifier in GPU

private:
	/**
	*	@brief Generates the texture as an unique color.
	*	@param color Values for each color channel.
	*/
	void loadColor(const vec4& color);

	/**
	*	@brief Generates the texture from an already loaded image.
	*	@param image Wrapper with an already loaded image.
	*	@param wrapS Mapping algorithm when coordinates textures exceeds the boundaries of the range [0, 1] (horizontal axis).
	*	@param wrapT Mapping algorithm when coordinates textures exceeds the boundaries of the range [0, 1] (vertical axis).
	*	@param minFilter Interpolation algorithm when texel size is bigger than pixel size.
	*	@param magFilter Interpolación algorithm when texel size is lower than pixel size.
	*	@return Success of instantiation.
	*/
	bool loadImage(UnsignedImage* image, const GLuint minFilter, const GLuint magFilter, const GLuint wrapS, const GLuint wrapT);

public:
	/**
	*	@brief Constructor from file.
	*/
	OpenGLTexture(const std::string& filename, const GLuint wrapS = WRAP_S, const GLuint wrapT = WRAP_T, const GLuint minFilter = MIN_FILTER, const GLuint magFilter = MAG_FILTER);

	/**
	*	@brief Constructor from an image already initialized.
	*/
	OpenGLTexture(UnsignedImage* image, const GLuint wrapS = WRAP_S, const GLuint wrapT = WRAP_T, const GLuint minFilter = MIN_FILTER, const GLuint magFilter = MAG_FILTER);

	/**
	*	@brief Constructor from an image given by a float array.
	*/
	OpenGLTexture(float* image, const int width, const int height, const bool isRGBA = true, const GLuint wrapS = WRAP_S, const GLuint wrapT = WRAP_T,
		const GLuint minFilter = MIN_FILTER, const GLuint magFilter = MAG_FILTER);

	/**
	*	@brief Constructor from an image given by a float array. Made for Noise Library, which returns the images in such shape.
	*/
	OpenGLTexture(std::vector<UnsignedImage*> images, const int width, const int height, const GLuint wrapS = WRAP_S, const GLuint wrapT = WRAP_T, const GLuint wrapR = WRAP_R,
		const GLuint minFilter = MIN_FILTER, const GLuint magFilter = MAG_FILTER);

	/**
	*	@brief Constructor of single color texture.
	*/
	OpenGLTexture(const vec4& color);

	/**
	*	@brief Destructor.
	*/
	virtual ~OpenGLTexture();

	/**
	*	@brief Applies a cube map texture by declarating shader uniform variables.
	*/
	void applyCubeMap(ShaderProgram* shader);

	/**
	*	@brief Applies texture by declarating shader uniform variables.
	*	@param shader Shader where we can specify the uniform values.
	*	@param textureType How to apply the texture to the shader.
	*/
	void applyTexture(ShaderProgram* shader, const TextureTypes textureType);

	/**
	*	@brief Flexible texture linking.
	*	@param shader Shader where we can specify the uniform values.
	*	@param id Texture slot.
	*	@param shaderVariable Texture name on shader (uniform variable).
	*/
	void applyTexture(ShaderProgram* shader, const GLint id, const std::string& shaderVariable);

	/**
	*	@brief Flexible texture linking.
	*	@param shader Shader where we can specify the uniform values.
	*	@param id Texture slot.
	*	@param shaderVariable Texture name on shader (uniform variable).
	*/
	void applyTexture4ComputeShader(ComputeShader* shader, const GLint id, const std::string& shaderVariable, const GLuint readWrite = GL_READ_ONLY, const GLuint format = GL_RGBA32F);

	// -------- Getters --------

	/**
	*	@eturn Identifier of texture.
	*/
	GLuint getIdentifier() { return _id; }
};
