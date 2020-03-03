#include "Light.h"


Light::Light(glm::vec3 a_position, glm::vec3 a_color, float a_specularStrength)
{

	m_position = a_position;
	m_color = a_color;
	m_specularStrength = a_specularStrength;
}
