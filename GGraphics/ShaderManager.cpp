#include "ShaderManager.h"


ShaderManager::ShaderManager()
{
	
}

ShaderManager::~ShaderManager()
{
	for (Shader* sh : m_ShaderList)
	{
		delete sh;
	}
}


// This is hard coded.
// Ideally I want a bunch of shaders to be created on application start and 
// a way to set them at runtime.
// Obsolete.
void ShaderManager::CreateShader()
{
	Shader* t = new Shader("Basic shader", "..\\Dependencies\\Shaders\\vert_with_normals.glsl", "..\\Dependencies\\Shaders\\simple_color_frag.glsl");
	m_ShaderList.push_back(t);
}

// Ideal shader constuctor.
void ShaderManager::CreateShader(const char* a_name, const char* a_vertLocation, const char* a_fragLocation)
{
	Shader* t = new Shader(a_name, a_vertLocation, a_fragLocation);
	m_ShaderList.push_back(t);
}




Shader* ShaderManager::FindShader(const char * a_name)
{
	for (Shader* sh : m_ShaderList)
	{
		if (sh->GetName() == a_name)
		{
			return sh;
		}
	}
	std::cout << "Shader " << a_name << " not found." << std::endl;
	return m_ShaderList[0];
}


Shader* ShaderManager::GetShader(const char * a_name)
{
	return FindShader(a_name);
}

// 0 == first element in array.
Shader* ShaderManager::GetShader(int a_index)
{
	if (a_index > m_ShaderList.size())
	{
		std::cout << "Could not find shader " + a_index << std::endl;
		return m_ShaderList[0];
	}
	return m_ShaderList[a_index];
}

