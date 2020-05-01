#include "ObjManager.h"




ObjManager::ObjManager(glm::mat4 *a_projectionView)
{
	m_projectionView = a_projectionView;
	 
}

// Memory leaks dawg fix this.
ObjManager::~ObjManager()
{
	for(Object * ob : m_modelList)
	{
		delete ob;
	}
	
	for(Light * lit : m_lights)
	{
		delete lit;
	}
}


void ObjManager::CreateLight(glm::vec3 a_position, glm::vec3 a_ambient, glm::vec3 a_diffuse, glm::vec3 a_specular,
	float a_shininess, float a_constant, float a_linear, float a_quadratic)
{
	Light* t = new Light(a_position, a_ambient, a_diffuse, a_specular, a_shininess, a_constant, a_linear, a_quadratic);
	m_lights.push_back(t);
}


// This is a mess and can be done MUCH better
// Load should take a string of the mesh it wants to use for this object. It should then 
// look for it in a manager and return a fail if not found. Same for texture. 
//void ObjManager::Load(const char* a_fileLocation, const char* a_name, const char* a_textureLocation)
//{
//	// Note that the creation of shaders needs to happen before loading of assests like this.
//	// This construcor is really quite bad.
//	// Each part needs a a load and a set. Or maybe a set since;
//	// Shaders are inteneded to have a manager and textures texures are intended to have a manager.
//	//											Vert												Frag										Texture								
//	Object* t = new Object(a_name, a_textureLocation);
//	//Object* t = new Object();
//	t->LoadModel(a_fileLocation);
//	t->SetModel(glm::translate(t->GetModel(), glm::vec3(m_modelList.size() * 10,0,0)));
//	m_modelList.push_back(t);
//}

void ObjManager::CreateObject(const char *a_objName /*= object*/)
{
	// For a safety thing... probably pointless like most of this but oh well.
	// After doing this I am 100% sure that this is dumb. But it can hang out
	// with the rest of the code.
	if (a_objName == "object")
	{
		Object* t = new Object("object" + m_modelList.size());
		t->SetModel(glm::translate(t->GetModel(), glm::vec3(0, 0, m_modelList.size() + 1 * 12)));
		//t->SetModel(glm::rotate(t->GetModel(), 90.0f, glm::vec3(0,1,0)));
		std::cout << t->GetModel()[3].x << " " << t->GetModel()[3].y << std::endl;
		m_modelList.push_back(t);
	}
	else
	{
		Object* t =	new Object(a_objName);
		//t->SetModel(glm::translate(t->GetModel(), glm::vec3(0, 0, m_modelList.size() + 1 * 12)));
		t->SetModel(glm::translate(t->GetModel(), glm::vec3(0, 0, -3)));
		//t->SetModel(glm::rotate(t->GetModel(), 90.0f, glm::vec3(0, 1, 0)));
		//std::cout << t->GetModel()[3].x << " " << t->GetModel()[3].y << std::endl;
		m_modelList.push_back(t);
	}
}


//void ObjManager::Load(const char* a_fileLocation, const char* a_name)
//{
//	// Note that the creation of shaders needs to happen before loading of assests like this.
//	// This construcor is really quite bad.
//	// Each part needs a a load and a set. Or maybe a set since;
//	// Shaders are inteneded to have a manager and textures texures are intended to have a manager.
//	//											Vert												Frag																		
//	//Object* t = new Object(a_name, "..\\Dependencies\\Shaders\\vert_with_normals.glsl", "..\\Dependencies\\Shaders\\simple_color_frag.glsl");
//	Object* t = new Object(a_name);
//
//	t->LoadModel(a_fileLocation);
//	t->SetModel(glm::translate(t->GetModel(), glm::vec3(m_modelList.size() * 10, 0, 0)));
//	m_modelList.push_back(t);
//}


// Utility for finding objects for assainments.
// Private.
// Make this a template and just search what is passed in?
// Better then multiple functions that do slightly different things.
Object* ObjManager::FindObject(const char* a_objectName)
{
	for (Object* ob : m_modelList)
	{
		if (ob->GetName() == a_objectName)
		{
			return ob;
		}
	}
	// No object of name found. Should return [0] just so it doesn't break.
	std::cout << "No object of name " + (std::string)a_objectName + " found." << std::endl;
	return nullptr;
	//return m_modelList[0];
}


void ObjManager::Draw(glm::mat4 &a_pv, glm::vec3 a_cameraPos)
{
	if (!m_modelList.empty())
	{
		for (int i = 0; i < m_modelList.size(); i++)
		{
			// Shader is null so that is why issues with drawing.
			// Create a manager for your shaders.
			// Think about how to attach s haders.
			// unsigned int shader_program_ID = m_modelList[i]->GetShader();
  			

			if (m_modelList[i]->GetShader() != nullptr)
			{
				unsigned int shader_program_ID = m_modelList[i]->GetShader()->GetShaderId();
				glUseProgram(shader_program_ID);


				// Texture assaignment moved to objmesh.
				/*if (m_modelList[i]->GetTexture() != nullptr)
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, m_modelList[i]->GetTexture()->GetDiffuse());
				}*/
				// Need access to sub meshes vao for meshes that have multiple 'peices' to them.
				// This also includes multiple seperate objects contained within one file.
				// Be aware that you have to bind the textures for the submesh then draw 
				// then unbind ect.

				


				auto uniform_location = glGetUniformLocation(shader_program_ID, "projection_view_matrix");
				glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(a_pv));
				//glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(*m_projectionView));

				// Since it's used again.
				int amountOfLights = (int)this->m_lights.size();

				uniform_location = glGetUniformLocation(shader_program_ID, "numberOfLights");
				glUniform1i(uniform_location, amountOfLights);
				
				// Passing for the lights.
				for (int i = 0; i < amountOfLights; i++)
				{
					// Every uniform needs to be passed individually 
					// This syntax sucks but lets do it.
					// Out stream? I feel like this is a bad way to do this.
					// I should be able to concatonate string literals and do that
					// instead.

					// m_lights[i]->m_position += glm::vec3((double)sin((double)glfwGetTime() * ((double)i + 1) * 0.000002f), 0, cos((double)glfwGetTime() * ((double)i + 1) * 0.000002f));
					
					std::ostringstream pos;

					pos << "lights[" << i << "].m_position";
					std::string uniformName0 = pos.str();

					uniform_location = glGetUniformLocation(shader_program_ID, uniformName0.c_str());
					glUniform3fv(uniform_location, 1, glm::value_ptr(m_lights[i]->m_position));

					std::ostringstream ambient;

					ambient << "lights[" << i << "].m_ambient";
					std::string uniformName1 = ambient.str();

					uniform_location = glGetUniformLocation(shader_program_ID, uniformName1.c_str());
					glUniform3fv(uniform_location, 1, glm::value_ptr(this->m_lights[i]->m_ambient));

					std::ostringstream diffuse;

					diffuse << "lights[" << i << "].m_diffuse";
					std::string uniformName2 = diffuse.str();

					uniform_location = glGetUniformLocation(shader_program_ID, uniformName2.c_str());
					glUniform3fv(uniform_location, 1, glm::value_ptr(this->m_lights[i]->m_diffuse));

					std::ostringstream specular;

					specular << "lights[" << i << "].m_specular";
					std::string uniformName3 = specular.str();

					uniform_location = glGetUniformLocation(shader_program_ID, uniformName3.c_str());
					glUniform3fv(uniform_location, 1, glm::value_ptr(this->m_lights[i]->m_specular));

					std::ostringstream shininess;

					shininess << "lights[" << i << "].m_shininess";
					std::string uniformName4 = shininess.str();

					uniform_location = glGetUniformLocation(shader_program_ID, uniformName4.c_str());
					glUniform1f(uniform_location, this->m_lights[i]->m_shininess);

					std::ostringstream constant;

					constant << "lights[" << i << "].m_constant";
					std::string uniformName5 = constant.str();

					uniform_location = glGetUniformLocation(shader_program_ID, uniformName5.c_str());
					glUniform1f(uniform_location, this->m_lights[i]->m_constant);

					std::ostringstream linear;

					linear << "lights[" << i << "].m_linear";
					std::string uniformName6 = linear.str();

					uniform_location = glGetUniformLocation(shader_program_ID, uniformName6.c_str());
					glUniform1f(uniform_location, this->m_lights[i]->m_linear);

					std::ostringstream quadratic;

					quadratic << "lights[" << i << "].m_quadratic";
					std::string uniformName7 = quadratic.str();

					uniform_location = glGetUniformLocation(shader_program_ID, uniformName7.c_str());
					glUniform1f(uniform_location, this->m_lights[i]->m_quadratic);

				}

				uniform_location = glGetUniformLocation(shader_program_ID, "cameraPostion");
				glUniform3fv(uniform_location, 1, glm::value_ptr(a_cameraPos));

				//m_modelList[i]->SetModel(glm::scale(m_modelList[i]->GetModel(), glm::vec3(100, 100, 0)));


				// Model to draw in worldspce
				uniform_location = glGetUniformLocation(shader_program_ID, "model_matrix");
				glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(m_modelList[i]->GetModel()));


				// The texturing and other shenanigans is in here.
				m_modelList[i]->Draw();
			}
		}
	}
}



// If texture manager set up.
// Needs an overloaded version for mesh chunks.
// It will need a number, as in meshchunk[a_meshChunk] in obj(a_name) texure is a_texture
// Or obj.GetMesh(a_meshChunk)
void ObjManager::SetTexture(const char* a_name, Texture* a_texture, unsigned int a_meshChunk /*= 0*/)
{
	Object* obj = FindObject(a_name);
	// Get mesh chunk.
	if (obj != nullptr)
	{
		obj->SetTexture(a_texture, a_meshChunk);
	}
}

void ObjManager::SetMesh(const char* a_name, OBJMesh* a_mesh)
{
	Object* obj = FindObject(a_name);
	if (obj != nullptr)
	{
		obj->SetMesh(a_mesh);
	}
}

//void ObjManager::SetMesh(const char* a_name, const char* a_meshLocation)
//{
//	Object* obj = FindObject(a_name);
//	obj->LoadModel(a_meshLocation);
//}


void ObjManager::SetShader(const char* a_name, Shader* a_shader)
{
	Object* obj = FindObject(a_name);
	if (obj != nullptr)
	{
		obj->SetShader(a_shader);
	}
}

void ObjManager::SetRigidBody(const char* a_name, PhysicsObject* a_rigidBody)
{
	Object* obj = FindObject(a_name);
	if (obj != nullptr)
	{
		obj->SetPhysicsObject(a_rigidBody);
	}
}