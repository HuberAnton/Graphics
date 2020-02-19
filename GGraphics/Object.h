#pragma once
#include "OBJMesh.h"

class Object
{
public:


	Object();

	void Draw();
	void LoadModel(const char* a_fileLocation);
	void LoadTexture(const char* a_textureLocation);

	glm::mat4 GetModel() { return m_modelMatrix; }

private:

	glm::mat4 m_modelMatrix;



	OBJMesh* mesh;
};

