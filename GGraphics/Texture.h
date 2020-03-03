#pragma once



// Sould handle all of the loading of textures and the identifier.
// Should be stored in a manager later down the line.

class Texture
{
public:
	Texture();
	Texture(const char * a_textureLocation);




	unsigned int GetDiffuse()	{ return m_diffuse; }
	bool SetDiffuse(const char* a_location);
	unsigned int GetSpecular()	{ return m_specular; }
	bool SetSpecular(const char* a_location);
	unsigned int GetNormals()	{ return m_normals; }
	bool SetNormal(const char* a_location);
private:
	// Need to add support.
	unsigned int m_diffuse;		// Slot 1
	unsigned int m_specular;	// Slot 2
	unsigned int m_normals;		// Slot 3
};

