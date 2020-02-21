#include "Object.h"
#include <iostream>


Object::Object(const char* vertex, const char* frag) : m_modelMatrix(1), m_shaderProgram(vertex, frag)
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



// This should not be here.
void Object::LoadTexture(const char* a_textureLocation)
{

}

