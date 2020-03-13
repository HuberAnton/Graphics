#include "Light.h"


Light::Light(glm::vec3 a_position, glm::vec3 a_ambient, glm::vec3 a_diffuse, glm::vec3 a_specular, 
	float a_shininess, float a_constant, float a_linear, float a_quadratic)
{
	m_position = a_position;

	m_ambient = a_ambient;
	m_diffuse = a_diffuse;
	m_specular = a_specular;


	m_shininess = a_shininess;

	m_constant = a_constant;
	m_linear = a_linear;
	m_quadratic = a_quadratic;
}
