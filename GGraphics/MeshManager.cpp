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

void MeshManager::CreateMesh(const char* a_name, PRIMITIVE a_prim, float a_size/* = 0*/, float  a_distanceFromOrigin/* = 0*/)
{
	std::vector<glm::vec4> verts;
	// Create verts then pass them in.
	// Maybe return verts.

	//int fragmentsWithoutCenter = 1000;

	int fragments = 90;
	float PI = 3.1415926f;
	float increment = 2.0f * PI / fragments;

	switch (a_prim)
	{
		// 0,0 is the center of the object with the square mesh around it.
	case PRIMITIVE::SQUARE:
		verts.push_back(glm::vec4(-a_size, -a_size, 0, 1));
		verts.push_back(glm::vec4(-a_size, a_size, 0, 1));
		verts.push_back(glm::vec4(a_size, a_size, 0, 1));

		verts.push_back(glm::vec4(-a_size, -a_size, 0, 1));
		verts.push_back(glm::vec4(a_size, a_size, 0, 1));
		verts.push_back(glm::vec4(a_size, -a_size, 0, 1));
		break;
	case PRIMITIVE::CIRCLE:
		// Need to add a vert for center point every... 1st? if(i/3 == 0) 0/3 = 0 right?

		for (int i = 0; i < fragments; i++)
		{
			// This isn't very good.
			// Makes the 1st point of every triangle in the circle the center
			// Then adds 1 more fragment. I could probably think of it more as
			// every 2 verts add 1 extra. This can be made much better if I make
			//  an IBO... Similar math but with some extras. 

			// Every i%3 == 0 for always using centre vert.
			// Then starting from the second triangle
			// i%2 == 0 { i - 1 }every second vert is the previous vert.


			if ((i % 2) == 0)
			{
				verts.push_back(glm::vec4(0, 0, 0, 1.0f));
				fragments++;
			}
			verts.push_back(glm::vec4(a_size * cos(i * increment), a_size * sin(i * increment), 0.0f, 1.0f));
		}

		/*for (float currentAngle = 0.0f; currentAngle <= 2.0f * PI; currentAngle += increment)
		{
			verts.push_back(glm::vec4(a_radius * cos(currentAngle), a_radius * sin(currentAngle), 0,1));
		}*/

		
		/*for (int i = 1; i < fragments + 2; i++)
		{
			verts.push_back(glm::vec4(a_radius * cos(i * increment), a_radius * sin(i * increment), 0.0f, 1.0f));
		}*/


		break;
	case PRIMITIVE::PLANE:
		verts.push_back(glm::vec4(-10, -0.1f, 0, 1));
		verts.push_back(glm::vec4(-10, 0.1f, 0, 1));
		verts.push_back(glm::vec4(10, 0.1f, 0, 1));

		verts.push_back(glm::vec4(-10, -0.1f, 0, 1));
		verts.push_back(glm::vec4(10, 0.1f, 0, 1));
		verts.push_back(glm::vec4(10, -0.1f, 0, 1));
		break;
	default:
		std::cout << "Problem with meshManger GenPrimsatives." << std::endl;
		system("pause");
		break;
	}
	OBJMesh* t = new OBJMesh(verts, a_name);
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
	std::cout << "Mesh " << a_name << " not found." << std::endl;
	return nullptr;
	//return m_meshList[0];
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

// Should I just do a switch? It's lazy but works.
// Maybe function pointers like for the physics collision?
void MeshManager::GeneratePrimitive(PRIMITIVE a_prim, std::vector<glm::vec3>& a_verts, float a_radius, float m_distanceFromOrigin)
{
	// The fact that I have to do this is not the best.
	int fragments = 1000000;
	float PI = 3.1415926f;
	float increment = (2.0f * PI) / fragments;

	switch (a_prim)
	{
		// 0,0 is the center of the object with the square mesh around it.
	case PRIMITIVE::SQUARE:
		a_verts.push_back(glm::vec3(-0.5f, -0.5f, 0));
		a_verts.push_back(glm::vec3(-0.5f, 0.5f , 0));
		a_verts.push_back(glm::vec3(0.5f, 0.5f, 0));

		a_verts.push_back(glm::vec3(-0.5f, -0.5f, 0));
		a_verts.push_back(glm::vec3(0.5f, 0.5f, 0));
		a_verts.push_back(glm::vec3(0.5f, -0.5f, 0));
		break;
	case PRIMITIVE::CIRCLE:
		for (float currentAngle = 0.0f; currentAngle <= 2.0f * PI; currentAngle += increment)
		{
			a_verts.push_back(glm::vec3(a_radius * cos(currentAngle), a_radius * sin(currentAngle), 0));
		}
		break;
	case PRIMITIVE::PLANE:

		break;
	default:
		std::cout << "Problem with meshManger GenPrimsatives." << std::endl;
		system("pause");
		break;
	}
}

