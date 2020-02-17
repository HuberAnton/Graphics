#pragma once
#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"


// Adams camrea class
// I just want it as a reference and compare to what I've done wrong.

class DemoCamera
{
public:

	DemoCamera();


	void setPerspective(float a_fov_y, float a_aspect_ratio, float a_near_distance, float a_far_distance);

	void setLookAt(glm::vec3 &a_fromPostion, glm::vec3 &a_toPosition, glm::vec3 &a_yawAxis);

	void setPostion(glm::vec3 &a_position);

	void setUp(glm::vec3& a_up);

	void setFacing(glm::vec3& a_facing);

	glm::mat4 getWorldTransform() {return m_worldMatrix;}

	glm::mat4 getView() { return m_viewMatrix; }

	glm::mat4 getProjection() { return m_projectionMatrix; }


	glm::mat4 getProjectionViewMatrix() { return m_projectionViewMatrix; }

private:

	void UpdateMatrices();


	float m_aspectRatio;

	glm::mat4 m_worldMatrix;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

	glm::mat4 m_projectionViewMatrix;

};

