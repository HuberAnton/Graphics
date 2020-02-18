#include "Application.h"


Application::Application()
{
	m_lastFrame = (float)glfwGetTime();
	m_deltaTime = 0;
}


// Does all the shenanigans needed for the u
void Application::UpdateApplication()
{
	float thisFrame = (float)glfwGetTime();
	m_deltaTime = thisFrame - m_lastFrame;
	m_lastFrame = thisFrame;
}


float Application::GetDeltaTime()
{
	return m_deltaTime;
}


