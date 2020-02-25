#include "Light.h"


Light::Light(glm::vec3 a_position, glm::vec3 a_diffuse, float a_specular)
{
	m_position = a_position;
	m_diffuse = a_diffuse;
	m_specular = a_specular;
}
