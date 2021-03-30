#pragma once

#include "Geometry/3D/AABB.h"
#include "Graphics/Core/Model3D.h"

/**
*	@file Group3D.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 07/09/2019
*/

/**
*	@brief Wrapper for several 3d models which inherites from Model3D.
*/
class Group3D: public Model3D
{
public:
	struct VolatileGPUData;
	struct VolatileGroupData;
	struct StaticGPUData;

protected:
	const static GLuint					BVH_BUILDING_RADIUS;			//!< Radius to search nearest neighbors in BVH building process
		
protected:
	AABB								_aabb;							//!< Boundaries of all those objects defined behind this group
	std::vector<ModelComponent*>		_globalModelComp;				//!< Wraps every model component from the group
	std::vector<Model3D*>				_objects;						//!< Elements which take part of the group

	// [GPU data]
	StaticGPUData*						_staticGPUData;					//!<

protected:
	/**
	*	@brief Builds the buffers which are necessary to build the BVH.
	*/
	void aggregateSSBOData(VolatileGPUData*& volatileGPUData, StaticGPUData*& staticGPUData);
	
	/**
	*	@brief Builds the input buffer which is neeeded as input array to generate BVH.
	*	@param sortedFaces GPU buffer where face indices are sortered according to their Morton codes.
	*/
	void buildClusterBuffer(VolatileGPUData* gpuData, const GLuint sortedFaces);

	/**
	*	@brief Computes the AABB which wraps all the triangles contained in this group.
	*	@param triangleBufferID To compute the AABB we need to define the triangle buffer in GPU, so that is saved to be reused.
	*/
	virtual AABB computeAABB(VolatileGroupData* groupData);

	/**
	*	@brief Computes the morton codes for each triangle boundind box.
	*/
	GLuint computeMortonCodes();

	/**
	*	@brief Rearranges the face array to sort it by morton codes.
	*	@param mortonCodes Computed morton codes from faces buffer.
	*/
	GLuint sortFacesByMortonCode(const GLuint mortonCodes);

public:
	/**
	*	@brief Constructor.
	*	@param modelMatrix Transformation to be applied for the whole group.
	*/
	Group3D(const mat4& modelMatrix = mat4(1.0f));

	/**
	*	@brief Destructor.
	*/
	virtual ~Group3D();

	/**
	*	@brief Adds a new component in the group array.
	*/
	void addComponent(Model3D* object);

	/**
	*	@brief Builds the BVH from scratch once the group is loaded.
	*/
	StaticGPUData* generateBVH();

	/**
	*	@brief Loads all those components who belong to this group, applying the model matrix linked to such group.
	*/
	virtual bool load(const mat4& modelMatrix = mat4(1.0f));

	/**
	*	@brief Assigns an id for a model component and registers it into an array.
	*/
	void registerModelComponent(ModelComponent* modelComp);

	/**
	*	@brief Extension from registerScene for inner nodes which are also groups.
	*/
	virtual void registerModelComponentGroup(Group3D* group);

	/**
	*	@brief Iterates through the group content to assign an id for each model component.
	*/
	void registerScene();

	/**
	*	@brief Updates the SSBO which maintains the data of every mesh in the scene.
	*/
	void updateMeshSSBO();

	// ------------------------- Getters -------------------------------

	/**
	*	@return Bounding volume of complete scene.
	*/
	AABB getAABB() { return _aabb; }

public:
	/**
	*	@brief
	*/
	struct VolatileGPUData
	{
		// [BVH]
		std::vector<BVHCluster>			_cluster;						//!< BVH nodes

		// [GPU buffers]
		GLuint							_tempClusterSSBO;				//!< Temporary buffer for BVH construction
		GLuint							_mortonCodesSSBO;				//!< Morton codes for each triangle

		/**
		*	@brief Default constructor.
		*/
		VolatileGPUData();

		/**
		*	@brief Destructor.
		*/
		~VolatileGPUData();
	};

	/**
	*	@brief
	*/
	struct VolatileGroupData
	{
		// [CPU generated data]
		std::vector<VertexGPUData>		_geometry;						//!< Global geometry
		std::vector<FaceGPUData>		_triangleMesh;					//!< Global face data
		std::vector<MeshGPUData>		_meshData;						//!< Global meshes
	};

	/**
	*	@brief 
	*/
	struct StaticGPUData
	{
		// [SSBO]
		GLuint							_groupGeometrySSBO;				//!< SSBO of group geometry
		GLuint							_groupTopologySSBO;				//!< SSBO of group faces
		GLuint							_groupMeshSSBO;					//!< SSBO of group meshes
		GLuint							_clusterSSBO;					//!< BVH nodes

		// [Metadata]
		unsigned						_numTriangles;					//!< Replaces cluster array data to release memory

		/**
		*	@brief Default constructor.
		*/
		StaticGPUData();

		/**
		*	@brief Destructor.
		*/
		~StaticGPUData();
	};
};

