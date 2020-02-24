#pragma once

#include "ObjManager.h"
#include "Object.h"
#include <vector>
#include "Shader.h"


class ObjManager
{

public:
	ObjManager(glm::mat4* a_projectionView);
	~ObjManager();
	void Draw(glm::mat4& a_pv, glm::vec3 a_cameraPos);
	void Load(const char * a_name, const char* a_fileLocation, const char* a_textureLocation);



private:
	std::vector<Object*> m_modelList;

	//Shader m_testShader;

	glm::mat4* m_projectionView;
};

