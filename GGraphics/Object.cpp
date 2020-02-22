#include "Object.h"
#include <iostream>


Object::Object(const char* vertex, const char* frag) : m_modelMatrix(1), m_shaderProgram(vertex, frag)
{
	
}

//Object::Object() : m_modelMatrix(1)
//{
//
//}


void Object::Draw()
{

	mesh->draw();
}


void Object::LoadModel(const char* a_fileLocation)
{
	mesh = new OBJMesh(a_fileLocation);

	if (mesh == NULL)
	{
		std::cout << "No mesh" << std::endl;
	}

}



