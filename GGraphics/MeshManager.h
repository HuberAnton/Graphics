#pragma once
#include <vector>
#include "OBJMesh.h"


enum class PRIMITIVE
{
	SQUARE,
	CIRCLE,
	PLANE
};




class MeshManager
{
public:
	MeshManager();
	~MeshManager();

	void CreateMesh(const char* a_name, const char* a_location);
	// Not a cool way to do this.
	void CreateMesh(const char* a_name, PRIMITIVE a_prim, float a_radius = 0, float  m_distanceFromOrigin = 0);

	OBJMesh* GetMesh(int a_index);
	OBJMesh* GetMesh(const char* a_name);

private:
	void GeneratePrimitive(PRIMITIVE a_prim, std::vector<glm::vec3>& a_verts, float a_radius, float  a_distanceFromOrigin);
	std::vector<OBJMesh*> m_meshList;
	OBJMesh* FindMesh(const char* a_name);
};
