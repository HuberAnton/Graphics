#include "DemoCamera.h"



DemoCamera::DemoCamera()
{
	m_worldMatrix = glm::mat4(1.0f);
	m_viewMatrix = glm::mat4(1.0f);
	m_projectionMatrix = glm::mat4(1.0f);
	m_projectionViewMatrix = glm::mat4(1.0f);
	//m_aspectRatio = 1.0f;
	m_aspectRatio = 16.0f / 9.0f;
	m_cameraSpeed = 3.0f;
	SetPerspective(3.14159f * 0.5f, m_aspectRatio, 0.01f, 100.0f);
	// Currently does not look at anything.
	//SetLookAt();
}



void DemoCamera::SetPerspective(float a_fov_y, float a_aspect_ratio,
	float a_near_distance, float a_far_distance)
{
	m_aspectRatio = a_aspect_ratio;
	m_projectionMatrix = glm::perspective(a_fov_y, a_aspect_ratio, a_near_distance, a_far_distance);
	UpdateMatrices();
}


void DemoCamera::SetLookAt(glm::vec3& a_fromPostion, glm::vec3& a_toPosition, glm::vec3& a_yawAxis)
{
	m_viewMatrix = glm::lookAt(a_fromPostion, a_toPosition, a_yawAxis);
	m_worldMatrix = glm::inverse(m_viewMatrix);
	UpdateMatrices();
}


void DemoCamera::UpdateMatrices()
{
	m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}


void DemoCamera::SetPostion(glm::vec3 &a_position)
{
	m_worldMatrix[3] = glm::vec4(a_position,1);
	m_viewMatrix = glm::inverse(m_worldMatrix);
}

// Probably not correct
void DemoCamera::SetUp(glm::vec3& a_up)
{

}
// Probably not correct.
void DemoCamera::SetFacing(glm::vec3& a_forward)
{

}


void DemoCamera::Update(float a_deltaTime)
{
	// Note this is the ideal way to get the window 
	// instead of passing it around.
	auto window = glfwGetCurrentContext();


}


void DemoCamera::Rotation()
{
	
	auto roration = glm::mat4(1.0f);
	//ro

}