#pragma once
#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include <iostream>
#include "ext.hpp"



class Light
{
public:
	Light(glm::vec3 a_direction, glm::vec3 a_color, float a_specularStrength);

	glm::vec3 m_position;
	glm::vec3 m_color;
	float m_specularStrength;
};
