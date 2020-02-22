#include "ObjManager.h"




ObjManager::ObjManager(glm::mat4 *a_projectionView)// : m_testShader("..\\Dependencies\\Shaders\\simple_vert.glsl", "..\\Dependencies\\Shaders\\simple_color_frag.glsl")
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
	//Object* t = new Object();

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

			// Shader is null so that is why issues with drawing.
			// Create a manager for your shaders.
			// Think about how to attach shaders.
			// unsigned int shader_program_ID = m_modelList[i]->GetShader();
			unsigned int shader_program_ID = m_modelList[i]->GetShader();

			glUseProgram(shader_program_ID);
			


			auto uniform_location = glGetUniformLocation(shader_program_ID, "projection_view_matrix");
			//glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(*m_projectionView));
			
			// Need to fix this. I need a reference to the pv in the class.
			glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(a_pv));
			uniform_location = glGetUniformLocation(shader_program_ID, "model_matrix");
			glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(m_modelList[i]->GetModel()));
			
			//glm::vec4 color = glm::vec4(sinf((float)glfwGetTime() * 0.2f),sinf((float)glfwGetTime()* 0.5f),cosf((float)glfwGetTime() * 0.1f),1);
			glm::vec3 modelColor = glm::vec3(1.0f, 0.5f, 0.31f);
			uniform_location = glGetUniformLocation(shader_program_ID, "modelColor");
			glUniform3fv(uniform_location, 1, glm::value_ptr(modelColor));


			uniform_location = glGetUniformLocation(shader_program_ID, "ambientStrength");
			glUniform1f(uniform_location, 0.3f);


			glm::vec3 ambientColor = glm::vec3(1, 1, 1);
			uniform_location = glGetUniformLocation(shader_program_ID, "ambientColor");
			glUniform3fv(uniform_location, 1, glm::value_ptr(ambientColor));



			//uniform_location = glGetUniformLocation(shader_program_ID, "color");
			//glUniform4fv(uniform_location, 1, glm::value_ptr(color));


			// The texturing and other shenanigans is in here.
			m_modelList[i]->Draw();

		}
	}
}

