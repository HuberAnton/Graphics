#pragma once
#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"


// Adams camrea class
// I just want it as a reference and compare to what I've done wrong.

enum class CAMERA_TYPE {
	PERSPECTIVE,
	ORTHO
};


class DemoCamera
{
public:

	// If I use this camera I probs need to have the different types of cameras
	// inherit most of this. The input handling would be different and the constructors
	// would need different info.
	
	DemoCamera(CAMERA_TYPE a_type);

	//Setters

	void SetPerspective(float a_fov_y, float a_near_distance, float a_far_distance);
	void SetOrtho(float a_near, float a_far);
	void SetLookAt(glm::vec3 a_fromPostion, glm::vec3 a_toPosition, glm::vec3 a_yawAxis);

	void SetPostion(glm::vec3 a_position);

	void SetRotation(glm::mat4 a_rotation);

	// Note that can get windo with current context.
	void Update(float a_deltaTime);

	// Getters
	// I feel some aren't neccesary but you never know.

	glm::mat4 GetWorldTransform() { return m_worldMatrix; }

	glm::mat4 GetView() { return m_viewMatrix; }

	glm::mat4 GetProjection() { return m_projectionMatrix; }
	
	glm::mat4* GetProjectionViewMatrix() { return &m_projectionViewMatrix; }

	// Pointer
	//glm::mat4* getProjectionViewMatrixP() { return &m_projectionViewMatrix; }
	
private:


	void UpdateMatrices();

	float m_aspectRatio;

	glm::mat4 m_worldMatrix;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_projectionViewMatrix;

	float m_cameraSpeed;
	float m_rotationSpeed;
	

	CAMERA_TYPE m_type;

	// Just so I don't have to create it each update.
	glm::vec3 m_displacementVector;
};

