#pragma once
#include "Texture.h"
#include <vector>


// This needs a system where it can take multiple
// maps and know 

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	void CreateTexture(const char * a_name, const char* a_location, bool a_flip);

	Texture* GetTexture(const char* a_name);
	Texture* GetTexture(int a_index);

private:
	// Note that 1 'Texture' contains
	// Diffuse, specular and normals.
	// Might be better having those in 
	// seperate lists.
	std::vector<Texture*> m_textureList;


	Texture* FindTexture(const char* a_name);
};

