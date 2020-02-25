#include "Object.h"
#include <iostream>



// Things to do make a primitive class
// Mesh should be created outside so should texture.


Object::Object(const char * a_name, const char* a_textureLocation) : m_modelMatrix(1),  m_texture(a_textureLocation)
{
	m_name = a_name;
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

