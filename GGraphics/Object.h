#pragma once
#include "OBJMesh.h"
#include "Shader.h"
#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include <iostream>
#include "ext.hpp"



class Object
{
public:


	Object(const char* vertex, const char* frag);
	Object();


	void Draw();
	void LoadModel(const char* a_fileLocation);

	void SetShader(Shader a_shader) { m_shaderProgram = a_shader; }
	unsigned int GetShader() { return m_shaderProgram.GetShaderId(); }

	glm::mat4 GetModel() { return m_modelMatrix; }
	void SetModel(glm::mat4 a_newPos) { m_modelMatrix = a_newPos; }
private:

	glm::mat4 m_modelMatrix;
	// Material - includes textures
	// This needs to be changed to a pointer when I have a shader manager.
	Shader m_shaderProgram;

	OBJMesh* mesh;
};

