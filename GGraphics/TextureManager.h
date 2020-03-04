#pragma once
#include "Texture.h"
#include <vector>


class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	void CreateTexture();

private:
	// Note that 1 'Texture' contains
	// Diffuse, specular and normals.
	// Might be better having those in 
	// seperate lists.
	std::vector<Texture*> m_textureList;

};

