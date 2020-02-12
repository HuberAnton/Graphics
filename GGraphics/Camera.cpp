#include "Camera.h"

// Default for test
Camera::Camera()
{
	m_cameraPostion = glm::vec3(0,0,-3.0f);	
	// Note the initial idea that you should change the 
	// target is incorrect and is in fact the center of the screen.
	// Meaning that it is derived from other coordinates.
	// m_cameraTarget = glm::vec3(0,0,0);

	m_up = glm::vec3(0,1,0);
	UpdateCamera();
}

// Called whenever the position or target is changed.
// I suppose up as well but I imagine changin the up will make 
// the camera controls kind of strange. Could it be used for rotation though?
// Wait no bad idea. Change the x and y of the camera direcion. 
// Some thinking about roll needs to happen I suppose.
void Camera::UpdateCamera()
{
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
	m_cameraPostion = -a_newPositoin;
	UpdateCamera();
}

