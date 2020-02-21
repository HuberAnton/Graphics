#pragma once

#include "ObjManager.h"
#include "Object.h"
#include <vector>

class ObjManager
{

public:
	ObjManager(glm::mat4* a_projectionView);
	~ObjManager();
	void Draw(glm::mat4& a_pv);
	void Load(const char* a_fileLocation);



private:
	std::vector<Object*> m_modelList;

	glm::mat4* m_projectionView;


};

