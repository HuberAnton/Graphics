#pragma once

#include "Shader.h"
#include <vector>


// TODO Need to make a selection of shaders with ways to be called.
// BONUS Include a way to recreate shaders.

class ShaderManager
{
public:
		ShaderManager();



private:
	// I need to have ways to access this information.
	std::vector<Shader*> ShaderList;
};

