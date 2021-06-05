#include "stdafx.h"
#include "Model3D.h"

#include "Graphics/Application/Renderer.h"
#include "Graphics/Core/Group3D.h"
#include "Graphics/Core/OpenGLUtilities.h"
#include "Graphics/Core/ShaderList.h"
#include "Graphics/Core/VAO.h"
#include "Utilities/FileManagement.h"
#include "Interface/Window.h"


// [Static variables initialization]

const GLuint Model3D::RESTART_PRIMITIVE_INDEX = 0xFFFFFFFF;


/// [Public methods]

Model3D::Model3D(const glm::mat4& modelMatrix) :
	_loaded(false), _modelMatrix(modelMatrix),  _modelComp(1)
{
	for (int i = 0; i < _modelComp.size(); ++i)
	{
		_modelComp[i] = new ModelComponent(this);
	}
}

Model3D::~Model3D()
{
	for (auto& it : _modelComp)
	{
		delete it;
	}
}

void Model3D::registerModelComponentGroup(Group3D* group)
{
	for (ModelComponent* modelComp : _modelComp)
	{
		group->registerModelComponent(modelComp);
	}
}

void Model3D::setMaterial(Material* material, unsigned slot)
{
	if (slot >= _modelComp.size())
	{
		return;
	}

	_modelComp[slot]->_material = material;
}

void Model3D::setMaterial(std::vector<Material*> material)
{
	int index = 0;

	while (index < _modelComp.size() && index < material.size())
	{
		_modelComp[index]->_material = material[index++];
	}
}


/// [Protected methods]

bool Model3D::readBinary(const std::string& filename, const std::vector<Model3D::ModelComponent*>& modelComp)
{
	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	if (!fin.is_open())
	{
		return false;
	}

	size_t numModelComps, numVertices, numTriangles;

	fin.read((char*)&numModelComps, sizeof(size_t));
	while (_modelComp.size() < numModelComps)
	{
		_modelComp.push_back(new ModelComponent(this));
	}

	for (Model3D::ModelComponent* model : modelComp)
	{
		fin.read((char*)&numVertices, sizeof(size_t));
		model->_geometry.resize(numVertices);
		fin.read((char*)&model->_geometry[0], numVertices * sizeof(Model3D::VertexGPUData));

		fin.read((char*)&numTriangles, sizeof(size_t));
		if (numTriangles > 0)
		{
			model->_topology.resize(numTriangles);
			fin.read((char*)&model->_topology[0], numTriangles * sizeof(Model3D::FaceGPUData));
		}

		fin.read((char*)&model->_modelDescription, sizeof(Model3D::ModelComponentDescription));
	}

	fin.close();

	return true;
}

bool Model3D::writeToBinary(const std::string& filename)
{
	std::ofstream fout(filename, std::ios::out | std::ios::binary);
	if (!fout.is_open())
	{
		return false;
	}

	const size_t numModelComps = _modelComp.size();
	fout.write((char*)&numModelComps, sizeof(size_t));

	for (Model3D::ModelComponent* model : _modelComp)
	{
		const size_t numVertices = model->_geometry.size();
		fout.write((char*)&numVertices, sizeof(size_t));
		fout.write((char*)&model->_geometry[0], numVertices * sizeof(Model3D::VertexGPUData));

		const size_t numTriangles = model->_topology.size();
		fout.write((char*)&numTriangles, sizeof(size_t));
		fout.write((char*)&model->_topology[0], numTriangles * sizeof(Model3D::FaceGPUData));

		fout.write((char*)&model->_modelDescription, sizeof(Model3D::ModelComponentDescription));
	}

	fout.close();

	return true;
}

/// MODEL COMPONENT SUBCLASS

/// [Public methods]

Model3D::ModelComponent::ModelComponent(Model3D* root) :
	_root(root), _id(-1), _material(nullptr)
{
}

Model3D::ModelComponent::~ModelComponent()
{
	
}

void Model3D::ModelComponent::assignModelCompIDFaces()
{
	for (FaceGPUData& data : _topology)
	{
		data._modelCompID = _id;
	}
}
