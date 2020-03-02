#pragma once

#include "ObjManager.h"
#include "Object.h"
#include <vector>
#include "Shader.h"
#include "Light.h"

class ObjManager
{

public:
	ObjManager(glm::mat4* a_projectionView);
	~ObjManager();
	void Draw(glm::mat4& a_pv, glm::vec3 a_cameraPos);
	void Load(const char * a_name, const char* a_fileLocation, const char* a_textureLocation);
	void Load(const char* a_fileLocation, const char* a_name);
	void CreateLight(glm::vec3 a_direction, glm::vec3 a_color, float a_specularStrength);

private:
	std::vector<Object*> m_modelList;
	std::vector<Light*> m_lights;

	glm::mat4* m_projectionView;
};

