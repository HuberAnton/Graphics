#include "DemoCamera.h"



DemoCamera::DemoCamera()
{
	m_worldMatrix = glm::mat4(1.0f);
	m_viewMatrix = glm::mat4(1.0f);
	m_projectionMatrix = glm::mat4(1.0f);
	m_projectionViewMatrix = glm::mat4(1.0f);
	m_aspectRatio = 1.0f;
}



void DemoCamera::setPerspective(float a_fov_y, float a_aspect_ratio,
	float a_near_distance, float a_far_distance)
{
	m_aspectRatio = a_aspect_ratio;
	m_projectionMatrix = glm::perspective(a_fov_y, a_aspect_ratio, a_near_distance, a_far_distance);
	UpdateMatrices();
}


void DemoCamera::setLookAt(glm::vec3& a_fromPostion, glm::vec3& a_toPosition, glm::vec3& a_yawAxis)
{
	m_viewMatrix = glm::lookAt(a_fromPostion, a_toPosition, a_yawAxis);
	m_worldMatrix = glm::inverse(m_viewMatrix);
	UpdateMatrices();
}


void DemoCamera::UpdateMatrices()
{
	m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}


void DemoCamera::setPostion(glm::vec3 &a_position)
{

}

// Probably not correct
void DemoCamera::setUp(glm::vec3& a_up)
{

}
// Probably not correct.
void DemoCamera::setFacing(glm::vec3& a_forward)
{

}