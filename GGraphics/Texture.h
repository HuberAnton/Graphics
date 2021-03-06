#pragma once
#include <vector>


// Sould handle all of the loading of textures and the identifier.
// Should be stored in a manager later down the line.


class Texture
{
public:
	Texture();
	Texture(const char * a_name);
	//Texture(const char* a_name, const char * a_textureLocation);


	const char* GetName() { return m_name; }

	unsigned int GetDiffuse()	{ return m_diffuse; }
	void SetDiffuse(const char* a_location, bool a_flip = false);
	unsigned int GetSpecular()	{ return m_specular; }
	void SetSpecular(const char* a_location, bool a_flip = false);
	unsigned int GetNormals()	{ return m_normals; }
	void SetNormal(const char* a_location, bool a_flip = false);
private:

	const char* m_name;


	// Need to add support.
	unsigned int m_diffuse;		// Slot 0
	unsigned int m_specular;	// Slot 1
	unsigned int m_normals;		// Slot 2
};

