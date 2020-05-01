#pragma once
#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "DemoCamera.h"


class Application
{
public:
	Application();

	void UpdateApplication();

	float GetDeltaTime();
	
	DemoCamera GetCamera() { return camera; }

private:
	float m_lastFrame;
	float m_deltaTime;

	DemoCamera camera;
	
	GLFWwindow* window;

};