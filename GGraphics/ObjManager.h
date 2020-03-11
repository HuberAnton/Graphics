#pragma once

#include "ObjManager.h"
#include "Object.h"
#include <vector>
#include "Shader.h"
#include "Light.h"
#include "Texture.h"

class ObjManager
{

public:
	ObjManager(glm::mat4* a_projectionView);
	~ObjManager();
	void Draw(glm::mat4& a_pv, glm::vec3 a_cameraPos);
	void Load(const char * a_name, const char* a_fileLocation, const char* a_textureLocation);
	void Load(const char* a_fileLocation, const char* a_name);
	void CreateObject(const char* a_objName = "object");

	void CreateLight(glm::vec3 a_direction, glm::vec3 a_color, float a_specularStrength);

	//void SetTexture(const char* a_name, const char* a_location, TEXTURE_TYPE a_type = TEXTURE_TYPE::DIFFUSE);
	// This is a placeholder until I place both inside of app.
	void SetTexture(const char* a_name, Texture* a_texture, unsigned int a_meshChunk = 0);


	// I really should have a templated set. They all
	void SetMesh(const char* a_name, OBJMesh* a_mesh);
	//void SetMesh(const char* a_name, const char* a_meshLocation);


	void SetShader(const char* a_name, Shader* a_shader);

private:
	std::vector<Object*> m_modelList;
	std::vector<Light*> m_lights;

	glm::mat4* m_projectionView;
	Object* FindObject(const char* a_objectName);
};

