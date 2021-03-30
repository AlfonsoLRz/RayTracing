#pragma once

#include "Graphics/Core/CGEnumerations.h"
#include "Graphics/Core/Material.h"
#include "Graphics/Core/ShaderProgram.h"
#include "objloader/OBJ_Loader.h"

class Group3D;

/**
*	@file Model3D.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 07/11/2019
*/

#define BINARY_EXTENSION ".bin"
#define OBJ_EXTENSION ".obj"

/**
*	@brief Base class for any drawable 3D model.
*/
class Model3D
{
public:
	class ModelComponent;

public:
	/**
	*	@brief Struct which wraps all that information for a mesh vertex.
	*/
	struct VertexGPUData
	{
		vec3		_position;
		float		_padding1;

		vec3		_normal;
		float		_padding2;

		vec2		_textCoord;
		vec2		_padding3;
	};

	/**
	*	@brief Struct which wraps a mesh data.
	*/
	struct FaceGPUData
	{
		uvec3		_vertices;
		unsigned	_modelCompID;							//!< ID of model component where the face belongs to

		vec3		_minPoint;								//!< Bounding box corner
		float		_padding1;

		vec3		_maxPoint;	
		float		_padding2;

		vec3		_normal;								//!< Accelerates LiDAR intersections 
		float		_padding3;
	};

	struct MeshGPUData
	{
		vec2		_padding1;
		unsigned	_numVertices;
		unsigned	_startIndex;
	};

	struct BVHCluster
	{
		vec3		_minPoint;
		unsigned	_prevIndex1;

		vec3		_maxPoint;
		unsigned	_prevIndex2;

		unsigned	_faceIndex;
		vec3		_padding;
		
		mat4 getScaleMatrix()
		{
			vec3 size = _maxPoint - _minPoint;

			return glm::scale(mat4(1.0f), size);
		}

		mat4 getTranslationMatrix()
		{
			vec3 center = (_maxPoint + _minPoint) / 2.0f;

			return glm::translate(mat4(1.0f), center);
		}
	};

	struct ModelComponentDescription
	{
		char	_materialName[40];
		vec3	_kd, _ks;
		float	_ns;
		char	_mapKd[60], _mapKs[60];

		/**
		*	@brief Default constructor for the initialization of a model component.
		*/
		ModelComponentDescription()
		{
			std::string emptyString = "";

			_kd = vec3(.0f);
			_ks = vec3(.0f);
			_ns = .0f;

			strcpy(_materialName, emptyString.c_str());
			strcpy(_mapKd, emptyString.c_str());
			strcpy(_mapKs, emptyString.c_str());
		}

		/**
		*	@brief Construction of description from the loading process.
		*/
		ModelComponentDescription(objl::Mesh* mesh)
		{
			objl::Material* material = &mesh->MeshMaterial;

			_kd = vec3(material->Kd.X, material->Kd.Y, material->Kd.Z);
			_ks = vec3(material->Ks.X, material->Ks.Y, material->Ks.Z);
			_ns = material->Ns;

			strcpy(_materialName, material->name.c_str());
			strcpy(_mapKd, material->map_Kd.c_str());
			strcpy(_mapKs, material->map_Ks.c_str());
		}

		/**
		*	@brief Assignment operator overriding.
		*/
		ModelComponentDescription& operator=(const ModelComponentDescription& description)
		{
			_kd = description._kd;
			_ks = description._ks;
			_ns = description._ns;

			strcpy(_materialName, description._materialName);
			strcpy(_mapKd, description._mapKd);
			strcpy(_mapKs, description._mapKs);

			return *this;
		}
	};

public:
	// [Rendering]
	const static GLuint				RESTART_PRIMITIVE_INDEX;		//!< Index which marks the end of a primitive

protected:
	bool							_loaded;				//!< Mark to know if model has already been loaded

	// [Geometry]
	std::vector<ModelComponent*>	_modelComp;				//!< One for each part of the mode, i.e. a revolution object with two bases and a body

	// [Matrices]
	glm::mat4						_modelMatrix;			//!< World transformation

protected:
	/**
	*	@brief Loads the CAD model from a binary file, if possible.
	*/
	virtual bool readBinary(const std::string& filename, const std::vector<Model3D::ModelComponent*>& modelComp);

	/**
	*	@brief Writes the model to a binary file in order to fasten the following executions.
	*	@return Success of writing process.
	*/
	virtual bool writeToBinary(const std::string& filename);

public:
	/**
	*	@brief Model 3D constructor.
	*	@param modelMatrix Transformation of model in world.
	*	@param numComponents Number of component which compose the model.
	*/
	Model3D(const mat4& modelMatrix = mat4(1.0f));

	/**
	*	@brief Copy constructor.
	*/
	Model3D(const Model3D& model) = delete;

	/**
	*	@brief Destructor.
	*/
	virtual ~Model3D();

	/**
	*	@return Model component located at the specified index.
	*/
	ModelComponent* getModelComponent(unsigned index) { return _modelComp[index]; }

	/**
	*	@return Model transformation matrix.
	*/
	mat4 getModelMatrix() { return _modelMatrix; }

	/**
	*	@brief Computes the model data and sends it to GPU.
	*	@param modelMatrix Model matrix to be applied while generating geometry.
	*	@return Success of operation.
	*/
	virtual bool load(const mat4& modelMatrix = mat4(1.0f)) = 0;

	/**
	*	@brief Assignment operator overriding.
	*/
	Model3D& operator=(const Model3D& model) = delete;

	/**
	*	@brief Assings identifier for each model component.
	*/
	virtual void registerModelComponentGroup(Group3D* group);

	/**
	*	@brief Establish the material as the color source for triangles.
	*	@param slot Component for which the material should be assigned.
	*/
	void setMaterial(Material* material, unsigned slot = 0);

	/**
	*	@brief Establish the material as the color source for triangles.
	*/
	void setMaterial(std::vector<Material*> material);

	/**
	*	@brief Assigns a new matrix for model transformation.
	*/
	void setModelMatrix(const mat4& modelMatrix) { _modelMatrix = modelMatrix; }
};

class Model3D::ModelComponent
{
public:
	// [Access variables]
	Model3D*					_root;
	unsigned					_id;

	// [GPU Data]
	std::vector<VertexGPUData>	_geometry;
	std::vector<FaceGPUData>	_topology;

	// [Additional info]
	Material*					_material;									//!< As many vector as material types for different shaders
	ModelComponentDescription   _modelDescription;

public:
	/**
	*	@brief Default constructor.
	*	@param root Model where this component is located.
	*/
	ModelComponent(Model3D* root);
	
	/**
	*	@brief Deleted copy constructor.
	*/
	ModelComponent(const ModelComponent& modelComp) = delete;

	/**
	*	@brief Destructor.
	*/
	~ModelComponent();

	/**
	*	@brief Assigns the identifier to each face of loaded topology.
	*/
	void assignModelCompIDFaces();

	/**
	*	@brief Assignment operator overriding.
	*/
	ModelComponent& operator=(const ModelComponent& orig) = delete;
};