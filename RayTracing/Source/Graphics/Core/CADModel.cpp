#include "stdafx.h"
#include "CADModel.h"

#include <filesystem>
#include "Graphics/Application/MaterialList.h"
#include "Graphics/Core/ShaderList.h"
#include "Graphics/Core/VAO.h"
#include "Utilities/FileManagement.h"

// Initialization of static attributes
std::unordered_map<std::string, std::unique_ptr<Material>> CADModel::_cadMaterials;
std::unordered_map<std::string, std::unique_ptr<Texture>> CADModel::_cadTextures;

/// [Public methods]

CADModel::CADModel(const std::string& filename, const std::string& textureFolder, const bool useBinary) : 
	Model3D(mat4(1.0f))
{
	_filename = filename;
	_textureFolder = textureFolder;
	_useBinary = useBinary;
}

CADModel::~CADModel()
{
}

bool CADModel::load(const mat4& modelMatrix)
{
	if (!_loaded)
	{
		bool success = false, binaryExists = false;

		if (_useBinary && (binaryExists = std::filesystem::exists(_filename + BINARY_EXTENSION)))
		{
			success = this->loadModelFromBinaryFile();
		}
			
		if (!success)
		{
			success = this->loadModelFromOBJ(modelMatrix);
		}

		if (!binaryExists && success)
		{
			this->writeToBinary(_filename + BINARY_EXTENSION);
		}

		_loaded = true;

		return _loaded;
	}

	return false;
}

/// [Protected methods]

void CADModel::computeMeshData(ModelComponent* modelComp)
{
	//ComputeShader* shader = ShaderList::getInstance()->getComputeShader(RendEnum::MODEL_MESH_GENERATION);
	//const int arraySize = modelComp->_topology.size();
	//const int numGroups = ComputeShader::getNumGroups(arraySize);

	//GLuint modelBufferID, meshBufferID, outBufferID;
	//modelBufferID = ComputeShader::setReadBuffer(modelComp->_geometry);
	//meshBufferID = ComputeShader::setReadBuffer(modelComp->_topology);
	//outBufferID = ComputeShader::setWriteBuffer(GLuint(), arraySize * 4);

	//shader->bindBuffers(std::vector<GLuint> { modelBufferID, meshBufferID, outBufferID });
	//shader->use();
	//shader->setUniform("size", arraySize);
	//shader->setUniform("restartPrimitiveIndex", Model3D::RESTART_PRIMITIVE_INDEX);
	//shader->execute(numGroups, 1, 1, ComputeShader::getMaxGroupSize(), 1, 1);

	//FaceGPUData* faceData = shader->readData(meshBufferID, FaceGPUData());
	//GLuint* rawMeshData = shader->readData(outBufferID, GLuint());
	//modelComp->_topology = std::move(std::vector<FaceGPUData>(faceData, faceData + arraySize));
	//modelComp->_triangleMesh = std::move(std::vector<GLuint>(rawMeshData, rawMeshData + arraySize * 4));

	//glDeleteBuffers(1, &modelBufferID);
	//glDeleteBuffers(1, &meshBufferID);
	//glDeleteBuffers(1, &outBufferID);
}

Material* CADModel::createMaterial(ModelComponent* modelComp)
{
	static const std::string nullMaterialName = "None";

	Material* material = MaterialList::getInstance()->getMaterial(CGApplicationEnumerations::MATERIAL_CAD_WHITE);
	Model3D::ModelComponentDescription* modelDescription = &modelComp->_modelDescription;
	std::string name = std::string(modelDescription->_materialName);
	std::string mapKd = std::string(modelDescription->_mapKd);
	std::string mapKs = std::string(modelDescription->_mapKs);

	if (!name.empty() && name != nullMaterialName)
	{
		auto itMaterial = _cadMaterials.find(name);

		if (itMaterial == _cadMaterials.end())
		{
			material = new Material();
			Texture* kad, * ks;

			if (!mapKd.empty())
			{
				kad = new Texture(_textureFolder + mapKd);
			}
			else
			{
				kad = new Texture(vec4(modelDescription->_kd, 1.0f));
			}

			if (!mapKs.empty())
			{
				ks = new Texture(_textureFolder + mapKs);
			}
			else
			{
				ks = new Texture(vec4(modelDescription->_ks, 1.0f));
				material->setShininess(modelDescription->_ns);
			}

			material->setTexture(Texture::KAD_TEXTURE, kad);
			material->setTexture(Texture::KS_TEXTURE, ks);

			_cadMaterials[name] = std::unique_ptr<Material>(material);
			_cadTextures[name + "-kad"] = std::unique_ptr<Texture>(kad);
			_cadTextures[name + "-ks"] = std::unique_ptr<Texture>(ks);
		}
		else
		{
			material = itMaterial->second.get();
		}
	}

	return material;
}

void CADModel::createModelComponent(objl::Mesh* mesh, ModelComponent* modelComp)
{
	VertexGPUData vertexData;

	for (int j = 0; j < mesh->Vertices.size(); j++)
	{
		vertexData._position = vec3(mesh->Vertices[j].Position.X, mesh->Vertices[j].Position.Y, mesh->Vertices[j].Position.Z);
		vertexData._normal = vec3(mesh->Vertices[j].Normal.X, mesh->Vertices[j].Normal.Y, mesh->Vertices[j].Normal.Z);
		vertexData._textCoord = vec2(mesh->Vertices[j].TextureCoordinate.X, mesh->Vertices[j].TextureCoordinate.Y);

		modelComp->_geometry.push_back(vertexData);
	}

	for (int j = 0; j < mesh->Indices.size(); j += 3)
	{
		modelComp->_topology.push_back(Model3D::FaceGPUData());
		modelComp->_topology[j / 3]._vertices = uvec3(mesh->Indices[j], mesh->Indices[j + 1], mesh->Indices[j + 2]);
		modelComp->_topology[j / 3]._modelCompID = modelComp->_id;
	}

	if (!modelComp->_material)
	{
		modelComp->_modelDescription = Model3D::ModelComponentDescription(mesh);
		modelComp->_material = this->createMaterial(modelComp);
	}
}

void CADModel::genGeometryTopology(Model3D::ModelComponent* modelComp, const mat4& modelMatrix)
{
	//ComputeShader* shader = ShaderList::getInstance()->getComputeShader(RendEnum::MODEL_APPLY_MODEL_MATRIX);
	//const int arraySize = modelComp->_geometry.size();
	//const int numGroups = ComputeShader::getNumGroups(arraySize);

	//GLuint modelBufferID;
	//modelBufferID = ComputeShader::setReadBuffer(modelComp->_geometry);

	//shader->bindBuffers(std::vector<GLuint> { modelBufferID});
	//shader->use();
	//shader->setUniform("mModel", modelMatrix * _modelMatrix);
	//shader->setUniform("size", arraySize);
	//if (modelComp->_material) modelComp->_material->applyMaterial4ComputeShader(shader);
	//shader->execute(numGroups, 1, 1, ComputeShader::getMaxGroupSize(), 1, 1);

	//VertexGPUData* data = shader->readData(modelBufferID, VertexGPUData());
	//modelComp->_geometry = std::move(std::vector<VertexGPUData>(data, data + arraySize));

	//this->computeMeshData(modelComp);

	//glDeleteBuffers(1, &modelBufferID);
}

bool CADModel::loadModelFromBinaryFile()
{
	bool success = true;

	if (success = this->readBinary(_filename +  BINARY_EXTENSION, _modelComp))
	{
		for (ModelComponent* modelComp : _modelComp)
		{
			modelComp->_material = this->createMaterial(modelComp);
		}
	}

	return success;
}

bool CADModel::loadModelFromOBJ(const mat4& modelMatrix)
{
	objl::Loader loader;
	bool success = loader.LoadFile(_filename + OBJ_EXTENSION);

	if (success)
	{
		while (_modelComp.size() < loader.LoadedMeshes.size())
		{
			_modelComp.push_back(new ModelComponent(this));
		}

		for (int i = 0; i < loader.LoadedMeshes.size(); i++)
		{
			this->createModelComponent(&(loader.LoadedMeshes[i]), _modelComp[i]);
			this->genGeometryTopology(_modelComp[i], modelMatrix);
		}
	}

	return success;
}