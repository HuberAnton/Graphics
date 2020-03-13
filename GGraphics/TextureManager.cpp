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
void TextureManager::SetTexture(const char* a_name, const char * a_location, bool a_flip, MAP_TYPE a_type /*= MAP_TYPE::DIFFUSE*/)
{
	Texture* t = FindTexture(a_name);
	if (t == nullptr)
	{
		std::cout << "Creating new texture" << std::endl;
		t = new Texture(a_name);
		m_textureList.push_back(t);
	}
	switch (a_type)
	{
	case MAP_TYPE::DIFFUSE:
		t->SetDiffuse(a_location, a_flip);
		break;
	case MAP_TYPE::NORMAL:
		 t->SetNormal(a_location, a_flip);
		break;
	case MAP_TYPE::SPECULAR:
		t->SetSpecular(a_location, a_flip);
		break;
	default:
		break;
	}
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
	return nullptr;
}
