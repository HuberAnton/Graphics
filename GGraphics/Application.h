#pragma once
#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"



class Application
{
public:
	Application();

	// Should be done at the start of everyframe?
	void UpdateApplication();

	float GetDeltaTime();
	

private:
	float m_lastFrame;
	float m_thisFrame;


	// This should contain the camera.
};

