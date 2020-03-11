#include "TextureManager.h"
#include <iostream>

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
	for (Texture* tex : m_textureList)
	{
		delete tex;
	}
}

// This is just going to be hardcoded.
// Ideally I would want this to read a file and load
// in the correct maps it finds.
void TextureManager::CreateTexture(const char* a_name, const char * a_location, bool a_flip)
{
	Texture* t = new Texture(a_name);
	t->SetDiffuse(a_location, a_flip);
	//t->SetNormal();
	//t->SetSpecular();
	m_textureList.push_back(t);
}

Texture* TextureManager::GetTexture(const char* a_name)
{
	return FindTexture(a_name);
}

Texture* TextureManager::GetTexture(int a_index)
{
	if (a_index > m_textureList.size())
	{
		std::cout << "Could not find texture " + a_index << std::endl;
		return m_textureList[0];
	}
	return m_textureList[a_index];
}

Texture* TextureManager::FindTexture(const char* a_name)
{
	for (Texture* tex : m_textureList)
	{
		if (tex->GetName() == a_name)
		{
			return tex;
		}
	}
	std::cout << "Texture " << a_name << " not found." << std::endl;
	return m_textureList[0];
}
