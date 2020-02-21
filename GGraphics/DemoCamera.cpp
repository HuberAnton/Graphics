#include "DemoCamera.h"



DemoCamera::DemoCamera() : m_worldMatrix(1), m_viewMatrix(1), m_projectionMatrix(1)
{
	m_aspectRatio = 16.0f / 9.0f;
	m_cameraSpeed = 1.0f;
	SetPerspective(3.14159f * 0.5f, m_aspectRatio, 0.01f, 100.0f);
	SetLookAt(glm::vec3(0,0,-3.0f), glm::vec3(0,0,0), glm::vec3(0,1,0));
}



void DemoCamera::SetPerspective(float a_fov_y, float a_aspect_ratio,
	float a_near_distance, float a_far_distance)
{
	m_aspectRatio = a_aspect_ratio;
	m_projectionMatrix = glm::perspective(a_fov_y, m_aspectRatio, a_near_distance, a_far_distance);
	UpdateMatrices();
}

void DemoCamera::SetLookAt(glm::vec3 a_camPosition, glm::vec3 a_lookPosition, glm::vec3 a_camUp)
{
	m_viewMatrix = glm::lookAt(a_camPosition, a_lookPosition, a_camUp);
	m_worldMatrix = glm::inverse(m_viewMatrix);
	UpdateMatrices();
}


void DemoCamera::UpdateMatrices()
{
	m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}

// Probably could combine this with rotation.
void DemoCamera::SetPostion(glm::vec3 a_position)
{
	m_worldMatrix[3] += glm::vec4(a_position,0);
	m_viewMatrix = glm::inverse(m_worldMatrix);
	UpdateMatrices();
}


// Probably could combine with postion.


// So this will need to use the forwardand adjust the look at fuction
// since rotation is basicaly changing the vector that makes the look position.
// That will cover pitch and yaw but I will need to think more about
// roll for the moment.
void DemoCamera::SetRotation(glm::mat4 a_rotation)
{

}







void DemoCamera::Update(float a_deltaTime)
{
	// Note this is the ideal way to get the window 
	// instead of passing it around.
	auto window = glfwGetCurrentContext();
	bool input = false;
	// Identity matrix
	m_displacementVector = glm::vec3(0);
	// A vector for storing the data.
	// I'll move it into the 

	// Movement

	if (glfwGetKey(window, GLFW_KEY_W))
	{
		m_displacementVector -= glm::vec3(m_worldMatrix[2]) * m_cameraSpeed * a_deltaTime;
		input = true;
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		m_displacementVector += glm::vec3(m_worldMatrix[2]) * m_cameraSpeed * a_deltaTime;
		input = true;
	}
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		m_displacementVector -= glm::vec3(m_worldMatrix[0]) * m_cameraSpeed * a_deltaTime;
		input = true;
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		m_displacementVector += glm::vec3(m_worldMatrix[0]) * m_cameraSpeed * a_deltaTime;
		input = true;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))
	{
		m_displacementVector -= glm::vec3(m_worldMatrix[1]) * m_cameraSpeed * a_deltaTime;
		input = true;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE))
	{
		m_displacementVector += glm::vec3(m_worldMatrix[1]) * m_cameraSpeed * a_deltaTime;
		input = true;
	}

	// Initialized mat4 with identity
	auto rotation = glm::mat4(1);

	//rotation = rotation * glm::rotate(float(m_rotationSpeed * a_deltaTime))



	if (input == true)
	{
		SetPostion(m_displacementVector);
	}
}


