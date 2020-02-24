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
// Load should take a string of the mesh it wants to use for this object. It should then 
// look for it in a manager and return a fail if not found. Same for texture. 
void ObjManager::Load(const char* a_fileLocation, const char* a_name, const char* a_textureLocation)
{
	// Note that the creation of shaders needs to happen before loading of assests like this.
	// This construcor is really quite bad.
	// Each part needs a a load and a set. Or maybe a set since;
	// Shaders are inteneded to have a manager and textures texures are intended to have a manager.
	//											Vert												Frag										Texture								
	Object* t = new Object(a_name ,"..\\Dependencies\\Shaders\\vert_with_normals.glsl", "..\\Dependencies\\Shaders\\simple_color_frag.glsl", a_textureLocation);
	//Object* t = new Object();

	t->LoadModel(a_fileLocation);
	t->SetModel(glm::translate(t->GetModel(), glm::vec3(m_modelList.size() * 10,0,0)));
	m_modelList.push_back(t);
}


void ObjManager::Draw(glm::mat4 &a_pv, glm::vec3 a_cameraPos)
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


			// This should be done better.
			if (m_modelList[i]->GetTexture() != NULL)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, m_modelList[i]->GetTexture());
			}

			auto uniform_location = glGetUniformLocation(shader_program_ID, "projection_view_matrix");
			glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(a_pv));
			//glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(*m_projectionView));
			
			glm::vec3 lightPos = glm::vec3(12, 12, 0);

			uniform_location = glGetUniformLocation(shader_program_ID, "lightPosition");
			glUniform3fv(uniform_location, 1, glm::value_ptr(lightPos));

			uniform_location = glGetUniformLocation(shader_program_ID, "cameraPostion");
			glUniform3fv(uniform_location, 1, glm::value_ptr(a_cameraPos));



			// Need to fix this. I need a reference to the pv in the class.
			uniform_location = glGetUniformLocation(shader_program_ID, "model_matrix");
			glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(m_modelList[i]->GetModel()));
			
			// Shenanigans! -  It startedfd working after it was placed below model and pv.
			// Could be that uniforms need to go in order to some degree? Like
			// First vertex uniforms THEN frag. 
			//glm::vec4 color = glm::vec4(sinf((float)glfwGetTime() * 0.2f),sinf((float)glfwGetTime()* 0.5f),cosf((float)glfwGetTime() * 0.1f),1);
			glm::vec3 modelColor = glm::vec3(1.0f, 0.5f, 0.31f);
			uniform_location = glGetUniformLocation(shader_program_ID, "modelColor");
			glUniform3fv(uniform_location, 1, glm::value_ptr(modelColor));

			uniform_location = glGetUniformLocation(shader_program_ID, "ambientStrength");
			glUniform1f(uniform_location, 0.2f);


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

