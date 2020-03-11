#include "MeshManager.h"
#include <iostream>

MeshManager::MeshManager()
{

}


MeshManager::~MeshManager()
{
	for (OBJMesh* mesh : m_meshList)
	{
		delete mesh;
	}
}

void MeshManager::CreateMesh(const char* a_name, const char* a_location)
{
	OBJMesh* t = new OBJMesh(a_location, a_name);
	m_meshList.push_back(t);
}



OBJMesh* MeshManager::FindMesh(const char* a_name)
{
	for (OBJMesh* msh : m_meshList)
	{
		if (msh->GetName() == a_name)
		{
			return msh;
		}
	}
	std::cout << "Shader " << a_name << " not found." << std::endl;
	return m_meshList[0];
}

// 0 is first element in array.
OBJMesh* MeshManager::GetMesh(int a_index)
{
	if (a_index > m_meshList.size())
	{
		std::cout << "Could not find mesh " + a_index << std::endl;
		return m_meshList[0];
	}
	return m_meshList[a_index];
}


OBJMesh* MeshManager::GetMesh(const char* a_name)
{
	return FindMesh(a_name);
}