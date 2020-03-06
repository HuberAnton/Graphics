#include "Object.h"
#include <iostream>


Object::Object(const char * a_name,const char* vertex, const char* frag, const char* a_textureLocation) : m_modelMatrix(1)
{
	m_name = a_name;
}

Object::Object(const char* a_name, const char* vertex, const char* frag) : m_modelMatrix(1)
{
	m_name = a_name;
	//m_texture = new Texture();
	//m_shaderProgram = new Shader("BasicShader", vertex, frag);
}

Object::Object(const char * a_name) : m_modelMatrix(1)
{
	m_name = a_name;
	
}

Object::~Object()
{
	// If these are assets will they need to be deleted?
	delete m_mesh;
	m_mesh = nullptr;
	m_texture = nullptr;
	m_shaderProgram = nullptr;
}

void Object::Draw()
{

	m_mesh->draw();
}

void Object::SetMesh(OBJMesh* a_mesh)
{
	m_mesh = a_mesh;
}

void Object::SetTexture(Texture* a_texture)
{
	m_texture = a_texture;
}

void Object::SetShader(Shader* a_shader) 
{ 
	m_shaderProgram = a_shader; 
}