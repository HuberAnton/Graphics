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


// Need to implement input processing after first making camera class.
//void Aplication::processInput(GLFWwindow* window)
//{
//
//        const float cameraSpeed = 0.05f; // adjust accordingly
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        cameraPos += cameraSpeed * cameraFront;
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        cameraPos -= cameraSpeed * cameraFront;
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//}