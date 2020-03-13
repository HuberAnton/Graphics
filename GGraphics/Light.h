#pragma once
#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include <iostream>
#include "ext.hpp"



class Light
{
public:
	Light(glm::vec3 a_position, glm::vec3 a_ambient, glm::vec3 a_diffuse, glm::vec3 a_specular, float a_shininess,
		float a_constant, float a_linear, float a_quadratic);

	glm::vec3 m_position;

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

	float m_constant;
	float m_linear;
	float m_quadratic;

	// Should really be stored from a material.
	float m_shininess;
	//float m_specularStrength;
};
