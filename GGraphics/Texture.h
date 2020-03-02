#pragma once
//#include "glm.hpp"
//#include "gl_core_4_5.h"
//#include "glfw3.h"
//#include <iostream>
//#include "ext.hpp"
//
//#include "..\stbimage\stb_image.h"


// Sould handle all of the loading of textures and the identifier.
// Should be stored in a manager later down the line.

class Texture
{
public:
	Texture();
	Texture(const char * a_textureLocation);




	unsigned int GetDiffuse()	{ return m_diffuse; }
	unsigned int GetSpecular()	{ return m_specular; }
	unsigned int GetNormals()	{ return m_normals; }
private:
	// Need to add support.
	unsigned int m_diffuse;		// Slot 1
	unsigned int m_specular;	// Slot 2
	unsigned int m_normals;		// Slot 3
};

