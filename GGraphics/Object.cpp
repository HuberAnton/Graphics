#include "Object.h"
#include <iostream>


Object::Object() : m_modelMatrix(1)
{

}


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


void Object::LoadTexture(const char* a_textureLocation)
{

}

