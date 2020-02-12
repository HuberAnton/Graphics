#include "Application.h"


Application::Application()
{
	m_thisFrame = 0;
	m_lastFrame = (float)glfwGetTime();
}


// Does all the shenanigans needed for the u
void Application::UpdateApplication()
{
	m_thisFrame = (float)glfwGetTime();
}


float Application::GetDeltaTime()
{
	return m_thisFrame - m_lastFrame;
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