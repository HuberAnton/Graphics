#pragma once

#include "Shader.h"
#include <vector>


// TODO Need to make a selection of shaders with ways to be called.
// BONUS Include a way to recreate shaders.

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();
	//void CreateShader(const char* a_name);
	void CreateShader();
	void CreateShader(const char* a_name, const char* a_vertLocation, const char* a_fragLocation);
	Shader* GetShader(const char* a_name);
	Shader* GetShader(int a_index);
private:
	// I need to have ways to access this information.
	std::vector<Shader*> m_ShaderList;
	Shader* FindShader(const char* a_name);
};