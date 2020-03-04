#include "Object.h"
#include <iostream>


Object::Object(const char * a_name,const char* vertex, const char* frag, const char* a_textureLocation) : m_modelMatrix(1)
{
	m_name = a_name;
}

Object::Object(const char* a_name, const char* vertex, const char* frag) : m_modelMatrix(1)
{
	m_name = a_name;
	m_texture = new Texture();
	m_shaderProgram = new Shader("BasicShader", vertex, frag);
}

Object::Object(const char * a_name)
{
	m_name = a_name;
	m_mesh = new OBJMesh();
	m_texture = new Texture();
	m_shaderProgram = new Shader();
}

Object::~Object()
{
	// If these are assets will they need to be deleted?
	delete m_mesh;
	delete m_texture;
	delete m_shaderProgram;
}



void Object::Draw()
{

	m_mesh->draw();
}

void Object::LoadModel(const char* a_fileLocation)
{
	m_mesh = new OBJMesh(a_fileLocation);

	if (m_mesh == NULL)
	{
		std::cout << "No mesh" << std::endl;
	}

}


void Object::SetTexture(Texture* a_texture)
{
	m_texture = a_texture;
}

void Object::SetMesh(OBJMesh* a_mesh)
{
	m_mesh = a_mesh;
}
