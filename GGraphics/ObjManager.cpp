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


void ObjManager::CreateLight(glm::vec3 a_direction, glm::vec3 a_color, float a_specularStrength)
{
	Light* t = new Light(a_direction, a_color, a_specularStrength);
	m_lights.push_back(t);
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

void ObjManager::CreateObject(const char *a_objName /*= object*/)
{
	// For a safety thing... probably pointless like most of this but oh well.
	// After doing this I am 100% sure that this is dumb. But it can hang out
	// with the rest of the code.
	if (a_objName == "object")
	{
		Object* t = new Object("object" + m_modelList.size());
		m_modelList.push_back(t);
	}
	else
	{
		Object* t =	new Object(a_objName);
		m_modelList.push_back(t);
	}
}


void ObjManager::Load(const char* a_fileLocation, const char* a_name)
{
	// Note that the creation of shaders needs to happen before loading of assests like this.
	// This construcor is really quite bad.
	// Each part needs a a load and a set. Or maybe a set since;
	// Shaders are inteneded to have a manager and textures texures are intended to have a manager.
	//											Vert												Frag																		
	Object* t = new Object(a_name, "..\\Dependencies\\Shaders\\vert_with_normals.glsl", "..\\Dependencies\\Shaders\\simple_color_frag.glsl");
	//Object* t = new Object();

	t->LoadModel(a_fileLocation);
	t->SetModel(glm::translate(t->GetModel(), glm::vec3(m_modelList.size() * 10, 0, 0)));
	m_modelList.push_back(t);
}


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
	return m_modelList[0];
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
  			unsigned int shader_program_ID = m_modelList[i]->GetShader();

			glUseProgram(shader_program_ID);


			// This should be done better.
			
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_modelList[i]->GetTexture()->GetDiffuse());
		
			// Need access to sub meshes vao for meshes that have multiple 'peices' to them.
			// This also includes multiple seperate objects contained within one file.
			// Be aware that you have to bind the textures for the submesh then draw 
			// then unbind ect.

			
			auto uniform_location = glGetUniformLocation(shader_program_ID, "projection_view_matrix");
			glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(a_pv));
			//glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(*m_projectionView));
			
			// Since it's used again.
 			int amountOfLights = this->m_lights.size();

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
				std::ostringstream pos;
				
				pos << "lights[" << i << "].position";
				std::string uniformName = pos.str();

				//uniform_location = glGetUniformLocation(shader_program_ID, "lights[" + i% + "].positon");


				uniform_location = glGetUniformLocation(shader_program_ID, uniformName.c_str());
				glUniform3fv(uniform_location, 1, glm::value_ptr(this->m_lights[i]->m_position));

				std::ostringstream color;
				
				color << "lights[" << i << "].color";
				std::string uniformName1 = color.str();

				uniform_location = glGetUniformLocation(shader_program_ID, uniformName1.c_str());
				glUniform3fv(uniform_location, 1, glm::value_ptr(this->m_lights[i]->m_color));

				std::ostringstream spec;

				spec << "lights[" << i << "].specularStrength";
				std::string uniformName2 = color.str();

				uniform_location = glGetUniformLocation(shader_program_ID, uniformName2.c_str());
				glUniform1f(uniform_location, this->m_lights[i]->m_specularStrength);
			}




			uniform_location = glGetUniformLocation(shader_program_ID, "cameraPostion");
			glUniform3fv(uniform_location, 1, glm::value_ptr(a_cameraPos));



			// Need to fix this. I need a reference to the pv in the class.
			uniform_location = glGetUniformLocation(shader_program_ID, "model_matrix");
			glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(m_modelList[i]->GetModel()));
			

			uniform_location = glGetUniformLocation(shader_program_ID, "ambientStrength");
			glUniform1f(uniform_location, 0.2f);


			glm::vec3 ambientColor = glm::vec3(1, 1, 1);
			uniform_location = glGetUniformLocation(shader_program_ID, "ambientColor");
			glUniform3fv(uniform_location, 1, glm::value_ptr(ambientColor));


			// The texturing and other shenanigans is in here.
			m_modelList[i]->Draw();

		}
	}
}

void ObjManager::SetTexture(const char* a_name, const char* a_location, TEXTURE_TYPE a_type /*= TEXTURE_TYPE::DIFFUSE*/)
{
	//Texture* t = FindObject(a_name)->GetTexture();

	//// Everything after this might be better being a part of the texture class.
	//switch (a_type)
	//{
	//case TEXTURE_TYPE::DIFFUSE:
	//	t->SetDiffuse(a_location);
	//	break;
	//case TEXTURE_TYPE::SPECULAR:
	//	t->SetSpecular(a_location); 
	//	break;
	//case TEXTURE_TYPE::NORMAL:
	//	t->SetNormal(a_location);
	//	break;
	//}
}

void ObjManager::SetTexture(const char* a_name, Texture* a_texure)
{
	Object* obj = FindObject(a_name);
	obj->SetTexture(a_texure);
}

void ObjManager::SetMesh(const char* a_name, OBJMesh* a_mesh)
{
	Object* obj = FindObject(a_name);
	obj->SetMesh(a_mesh);
}