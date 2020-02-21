#include "ObjManager.h"




ObjManager::ObjManager(glm::mat4* a_projectionView)
{
	m_projectionView = a_projectionView;
}



// This is a mess and can be done MUCH better
void ObjManager::Load(const char* a_fileLocation)
{
	Object* t = new Object("..\\Dependencies\\Shaders\\simple_vert.glsl", "..\\Dependencies\\Shaders\\simple_color_frag.glsl");
	t->LoadModel(a_fileLocation);
	m_modelList.push_back(t);
}


void ObjManager::Draw()
{
	if (!m_modelList.empty())
	{
		for (int i = 0; i < m_modelList.size(); i++)
		{
			auto shader_program_ID = m_modelList[i]->GetShader();
			glUseProgram(shader_program_ID);
			


			auto uniform_location = glGetUniformLocation(shader_program_ID, "projection_view_matrix");
			glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(*m_projectionView));
			uniform_location = glGetUniformLocation(m_modelList[i]->GetShader(), "model_matrix");
			glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(m_modelList[i]->GetModel()));

			// The texturing and other shenanigans is in here.
			m_modelList[i]->Draw();
		}
	}
}

