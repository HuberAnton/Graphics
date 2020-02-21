#include "ObjManager.h"




ObjManager::ObjManager(glm::mat4* a_projectionView)
{
	m_projectionView = a_projectionView;
}

// Memory leaks dawg fix this.
ObjManager::~ObjManager()
{
	//for(int i = ; i)
}



// This is a mess and can be done MUCH better
void ObjManager::Load(const char* a_fileLocation)
{
	Object* t = new Object("..\\Dependencies\\Shaders\\simple_vert.glsl", "..\\Dependencies\\Shaders\\simple_color_frag.glsl");
	t->LoadModel(a_fileLocation);
	t->SetModel(glm::translate(t->GetModel(), glm::vec3(m_modelList.size() * 10,0,0)));
	m_modelList.push_back(t);
}


void ObjManager::Draw(glm::mat4 &a_pv)
{
	if (!m_modelList.empty())
	{
		for (int i = 0; i < m_modelList.size(); i++)
		{
			unsigned int shader_program_ID = m_modelList[i]->GetShader();
			glUseProgram(shader_program_ID);
			


			auto uniform_location = glGetUniformLocation(shader_program_ID, "projection_view_matrix");
			//glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(*m_projectionView));
			
			// Need to fix this.
			glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(a_pv));
			uniform_location = glGetUniformLocation(shader_program_ID, "model_matrix");
			glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(m_modelList[i]->GetModel()));
			
			uniform_location = glGetUniformLocation(shader_program_ID, "color");
			glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(glm::vec4(1,0,0,1)));


			// The texturing and other shenanigans is in here.
			m_modelList[i]->Draw();
		}
	}
}

