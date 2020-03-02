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



class Object
{
public:


	Object(const char * a_name, const char* vertex, const char* frag, const char* a_textureLocation);
	Object(const char* a_name, const char* vertex, const char* frag);

	~Object();

	void Draw();
	void LoadModel(const char* a_fileLocation);

	void SetShader(Shader a_shader) { m_shaderProgram = a_shader; }

	unsigned int GetShader() { return m_shaderProgram.GetShaderId(); }

	Texture GetTexture() { return m_texture; }

	
	glm::mat4 GetModel() { return m_modelMatrix; }
	void SetModel(glm::mat4 a_newPos) { m_modelMatrix = a_newPos; }
private:
	const char* m_name;
	
	// This should be a pointer and might need a different name since it's
	// a bit... lacking.
	Texture m_texture;
	

	glm::mat4 m_modelMatrix;
	// Material - includes textures
	// This needs to be changed to a pointer when I have a shader manager.
	Shader m_shaderProgram;

	OBJMesh* mesh;
};

