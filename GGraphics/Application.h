#pragma once
#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "DemoCamera.h"


class Application
{
public:
	Application();

	// Should be done at the start of everyframe?
	void UpdateApplication();

	float GetDeltaTime();
	

	


	DemoCamera GetCamera() { return camera; }

private:
	float m_lastFrame;
	float m_deltaTime;

	DemoCamera camera;

	
	GLFWwindow* window;

	// This should contain the camera.
};