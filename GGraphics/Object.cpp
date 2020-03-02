#include "Object.h"
#include <iostream>


Object::Object(const char * a_name,const char* vertex, const char* frag, const char* a_textureLocation) : m_modelMatrix(1), m_shaderProgram(vertex, frag), m_texture(a_textureLocation)
{
	m_name = a_name;
}

Object::Object(const char* a_name, const char* vertex, const char* frag) : m_modelMatrix(1), m_shaderProgram(vertex, frag)
{
	m_name = a_name;
}


Object::~Object()
{
	delete mesh;
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



