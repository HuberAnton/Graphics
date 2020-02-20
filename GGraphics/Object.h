#pragma once
#include "OBJMesh.h"
#include "glm.hpp"


class Object
{
public:

	struct Vertex
	{
		glm::vec4 position;		// attrib location 0
		glm::vec4 normal;		// attric location 1
		glm::vec2 texcoord;		// attrib locatoin 2
	};



	Object();

	void Draw();
	void LoadModel(const char* a_fileLocation);
	void LoadTexture(const char* a_textureLocation);

	glm::mat4 GetModel() { return m_modelMatrix; }

private:

	glm::mat4 m_modelMatrix;



	OBJMesh* mesh;
};

