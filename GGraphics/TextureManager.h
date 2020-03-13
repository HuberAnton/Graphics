#pragma once
#include "Texture.h"
#include <vector>


// This needs a system where it can take multiple
// maps and know 

enum class MAP_TYPE
{
	DIFFUSE,
	NORMAL,
	SPECULAR
};





class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	void SetTexture(const char * a_name, const char* a_location, bool a_flip, MAP_TYPE a_type = MAP_TYPE::DIFFUSE);

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

