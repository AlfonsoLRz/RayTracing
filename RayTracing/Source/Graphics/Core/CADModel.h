#pragma once

#include "Graphics/Core/Model3D.h"
#include "objloader/OBJ_Loader.h"

/**
*	@file CADModel.h
*	@authors Alfonso L�pez Ruiz (alr00048@red.ujaen.es)
*	@date 11/28/2020
*/

/**
*	@brief Model loaded from an OBJ file.
*/
class CADModel: public Model3D
{
protected:
	static std::unordered_map<std::string, std::unique_ptr<Material>>	_cadMaterials;
	static std::unordered_map<std::string, std::unique_ptr<Texture>>	_cadTextures;

protected:
	std::string		_filename;				//!< File path (without extension)
	std::string		_textureFolder;			//!< Folder where model textures may be located
	bool			_useBinary;				//!< Use binary file instead of original obj models

protected:
	/**
	*	@brief Computes a triangle mesh buffer composed only by indices.
	*/
	void computeMeshData(Model3D::ModelComponent* modelComp);

	/**
	*	@brief Creates a new material from the attributes of a model component.
	*/
	Material* createMaterial(ModelComponent* modelComp);

	/**
	*	@brief Initializes a model component with the content of a mesh.
	*/
	void createModelComponent(objl::Mesh* mesh, ModelComponent* modelComp);

	/**
	*	@brief Generates geometry via GPU.
	*/
	void genGeometryTopology(Model3D::ModelComponent* modelComp, const mat4& modelMatrix);

	/**
	*	@brief Fills the content of model component with binary file data.
	*/
	bool loadModelFromBinaryFile();

	/**
	*	@brief Generates geometry via GPU.
	*/
	bool loadModelFromOBJ(const mat4& modelMatrix);

public:
	/**
	*	@brief CADModel constructor.
	*	@param filename Path where the model is located.
	*	@param useBinary Use of previously written binary files.
	*/
	CADModel(const std::string& filename, const std::string& textureFolder, const bool useBinary);

	/**
	*	@brief Deleted copy constructor.
	*	@param model Model to copy attributes.
	*/
	CADModel(const CADModel& model) = delete;

	/**
	*	@brief Destructor.
	*/
	virtual ~CADModel();

	/**
	*	@brief Loads the model data from file.
	*	@return Success of operation.
	*/
	virtual bool load(const mat4& modelMatrix = mat4(1.0f));

	/**
	*	@brief Deleted assignment operator.
	*	@param model Model to copy attributes.
	*/
	CADModel& operator=(const CADModel& model) = delete;
};

