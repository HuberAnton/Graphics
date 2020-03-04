#include "TextureManager.h"


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
void TextureManager::CreateTexture()
{
	Texture* t = new Texture();
	t->SetDiffuse("..\\Dependencies\\Textures\\Scrabble.jpg");
	//t->SetNormal();
	//t->SetSpecular();
	m_textureList.push_back(t);
}
