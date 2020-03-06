#pragma once
#include <vector>
#include "OBJMesh.h"



class MeshManager
{
public:
	MeshManager();
	~MeshManager();

	void CreateMesh(const char* a_location, const char* a_name);

	OBJMesh* GetMesh(int a_index);
	OBJMesh* GetMesh(const char* a_name);

private:

	std::vector<OBJMesh*> m_meshList;

	OBJMesh* FindMesh(const char* a_name);
};
