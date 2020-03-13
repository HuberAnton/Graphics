#pragma once
#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"


/*
Note that the exaple on canvas has tricount and all parts needed for shaders.(Vao, vbo, ibo)
It is assumed that you would bind the shaders.

*/

// NOT USED. Use OBJmesh instead.

class Mesh
{
public:
	Mesh() : triCount(0), m_vao(0), m_vbo(0), m_ibo(0) {};
	virtual ~Mesh();


	struct Vertex 
	{
		glm::vec4 postion;
		glm::vec4 normal;
		glm::vec2 Uv;
	};

	void InitialiseQuad();

	virtual void Draw();


private:
	unsigned int triCount;

	// Note that these will need to be removed from main
	// as well as any other binds and gens since they are now handled
	// within the class.
	unsigned m_vao, m_vbo, m_ibo;
};