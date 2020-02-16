#pragma once

#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include <iostream>
#include <fstream>
#include <sstream>

class Shader
{
public:
	Shader(std::string a_vectorLocation, std::string a_fragmentShader);

	unsigned int GetShaderId() { return m_shaderProgramId; }
private:
	unsigned int m_shaderProgramId;
};
