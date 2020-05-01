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
#include "PhysicsObject.h"

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

	// This is hacky and I don't like it.
	void FixedUpdate(glm::vec2 a_gravity, float a_timeStep);

	PhysicsObject* GetPhysicsObject() {return m_rigidBody; }
	// This might cause issues.
	void SetPhysicsObject(PhysicsObject* a_physiscsObject) { m_rigidBody = a_physiscsObject; }


	glm::mat4 GetModel() { return m_modelMatrix; }
	void SetModel(glm::mat4 a_newPos) { m_modelMatrix = a_newPos; }
	
	void SetPosition(glm::vec3 a_newPos) { m_modelMatrix[3] = glm::vec4(a_newPos, 1); }
	glm::vec4 GetPosition() { return m_modelMatrix[3]; }
private:
	const char* m_name;
	
	// Bad name. Actually transform.
	glm::mat4 m_modelMatrix;

	// Should probably stick to the rigidbody for the time being then
	// seperate them
	PhysicsObject* m_rigidBody = nullptr;
	// Collider m_collider = nullptr;
	// Note that these 3 should store a reference of these assets.
	Shader* m_shaderProgram = nullptr;
	Texture* m_texture = nullptr;
	OBJMesh* m_mesh = nullptr;
};
