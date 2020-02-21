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

	// If I use this camera I probs need to have the different types of cameras
	// inherit most of this. The input handling would be different and the constructors
	// would need different info.

	DemoCamera();

	//Setters

	void SetPerspective(float a_fov_y, float a_aspect_ratio, float a_near_distance, float a_far_distance);

	void SetLookAt(glm::vec3 a_fromPostion, glm::vec3 a_toPosition, glm::vec3 a_yawAxis);

	void SetPostion(glm::vec3 a_position);

	void SetRotation(glm::mat4 a_rotation);

	// Note that can get windo with current context.
	void Update(float a_deltaTime);

	// Getters
	// I feel some aren't neccesary but you never know.

	glm::mat4 getWorldTransform() { return m_worldMatrix; }

	glm::mat4 getView() { return m_viewMatrix; }

	glm::mat4 getProjection() { return m_projectionMatrix; }
	
	glm::mat4 getProjectionViewMatrix() { return m_projectionViewMatrix; }

	// Pointer
	glm::mat4* getProjectionViewMatrixP() { return &m_projectionViewMatrix; }
	
private:


	void UpdateMatrices();

	float m_aspectRatio;

	glm::mat4 m_worldMatrix;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_projectionViewMatrix;

	float m_cameraSpeed;
	float m_rotationSpeed;

	// Just so I don't have to create it each update.
	glm::vec3 m_displacementVector;
};

