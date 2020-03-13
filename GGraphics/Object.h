#pragma once
#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include <iostream>
#include "ext.hpp"
#include "Shader.h"
#include "OBJMesh.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "OBJMesh.h"


class Object
{
public:


	Object(const char * a_name, const char* vertex, const char* frag, const char* a_textureLocation);
	Object(const char* a_name, const char* vertex, const char* frag);
	Object(const char* a_name);

	~Object();

	void Draw();

	Shader* GetShader() { return m_shaderProgram; }
	void SetShader(Shader* a_shader);
	OBJMesh* GetMesh() { return m_mesh; }
	void SetMesh(OBJMesh* a_mesh);
	

	Texture* GetTexture() { return m_texture; }
	void SetTexture(Texture* a_texture, unsigned int a_meshChunk);
	const char* GetName() { return m_name; }



	glm::mat4 GetModel() { return m_modelMatrix; }
	void SetModel(glm::mat4 a_newPos) { m_modelMatrix = a_newPos; }
private:
	const char* m_name;
	


	glm::mat4 m_modelMatrix;


	// Note that these 3 should copy assets.
	Shader* m_shaderProgram = nullptr;
	Texture* m_texture = nullptr;
	OBJMesh* m_mesh = nullptr;
};

