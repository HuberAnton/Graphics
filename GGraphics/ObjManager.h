#pragma once

#include "ObjManager.h"
#include "Object.h"
#include <vector>
#include "Shader.h"
#include "Light.h"
#include "Texture.h"
#include "PhysicsObject.h"


class ObjManager
{

public:
	ObjManager(glm::mat4* a_projectionView);
	~ObjManager();
	void Draw(glm::mat4& a_pv, glm::vec3 a_cameraPos);
	void CreateObject(const char* a_objName = "object");

	void CreateLight(glm::vec3 a_position, glm::vec3 a_ambient, glm::vec3 a_diffuse, glm::vec3 a_specular,
		float a_shininess, float a_constant, float a_linear, float a_quadratic);

	
	// This is a placeholder until I place both inside of app.
	void SetTexture(const char* a_name, Texture* a_texture, unsigned int a_meshChunk = 0);


	// I really should have a templated set?
	void SetMesh(const char* a_name, OBJMesh* a_mesh);

	// Everything that creates a rigidboy gets passed in here so it can then
	// be created.
	void SetRigidBody(const char* a_name, PhysicsObject* a_rigidBody);

	void SetShader(const char* a_name, Shader* a_shader);

	Object* FindObject(const char* a_objectName);
private:
	std::vector<Object*> m_modelList;
	std::vector<Light*> m_lights;

	glm::mat4* m_projectionView;
};

