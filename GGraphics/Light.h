#pragma once
#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include <iostream>
#include "ext.hpp"



class Light
{
public:
	Light();




	glm::vec3 m_direction;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
};

