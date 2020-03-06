#pragma once
#include "Texture.h"
#include <vector>


class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	void CreateTexture(const char* a_location);

	//Texture* GetTexture(const char* a_name);
	Texture* GetTexture(int a_index);

private:
	// Note that 1 'Texture' contains
	// Diffuse, specular and normals.
	// Might be better having those in 
	// seperate lists.
	std::vector<Texture*> m_textureList;


	//Texture* FindTexture(const char* a_name);
};

