#include "Camera.h"

// Default for test
Camera::Camera()
{
	// Camera starts off at 0.
	m_cameraPostion = glm::vec3(1);	
	// Camera facing is set and note that this value
	// is only ever adjusted when you start rotation.
	// If you think about it it makes sense. 
	// The camera positon + the 
	m_up = glm::vec3(0,1,0);
	m_cameraFront = glm::vec3(0, 0, -1.0f);
	m_yaw = -90.0f;
	m_pitch = 1;
	
	UpdateCamera();
}

// Called whenever the position or target is changed.
// I suppose up as well but I imagine changin the up will make 
// the camera controls kind of strange. Could it be used for rotation though?
// Wait no bad idea. Change the x and y of the camera direcion. 
// Some thinking about roll needs to happen I suppose.
void Camera::UpdateCamera()
{
	glm::vec3 front;
	// I will have to change this to Quartonians
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_cameraFront = glm::normalize(front);
	m_cameraRight = glm::normalize(glm::cross(m_cameraFront, m_up));
	m_cameraUp = glm::normalize(glm::cross(m_cameraRight, m_cameraFront));


	//m_viewMatrix = glm::lookAt(m_cameraPostion, , m_up);
	m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
}

// Should be called during constructor and when
// any fov or aspect ratio changes occur.
// I could query the window after the window size is changed
// and then adjust the window accordingly.
// It may need an overload if I go that way.
glm::mat4 Camera::GetPerspeciveMatrix()
{	
	return m_projectionMatrix = glm::perspective(1.507f, 16.0f / 9.0f, 0.1f, 50.0f);
}

// I don't think this is correct either.
void Camera::SetPosition(glm::vec3 a_newPositoin)
{
	m_cameraPostion += a_newPositoin;
	UpdateCamera();
}

