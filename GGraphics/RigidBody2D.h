#pragma once

#include "glm.hpp"
#include "PhysicsObject.h"


class RigidBody2D : public PhysicsObject
{
public:
	// Will need to know what the shape of the rigid body is.
	// Consider adding an offset so the rigidbody can be seperate/moved independantly
	//RigidBody2D();
	/*RigidBody2D(ShapeType a_shape, glm::vec2 a_position, glm::vec2 a_velocity,
		 float a_mass);*/
	//~RigidBody2D();
	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timeStep);
	void ApplyForce(glm::vec2 a_force);
	void ApplyForceToActor(RigidBody2D* a_actor, glm::vec2 a_force);


	// I'm going to have issues with this working with my model matirx possibly.
	glm::vec2 GetPosition() { return m_position; }
	void SetPosition(glm::vec2 a_position) { m_position = a_position; }
	glm::vec2 GetVelocity() { return m_velocity; }
	float GetMass() { return m_mass; }


	void ResolveCollision(RigidBody2D* a_actor, glm::vec2 a_collsionNormal);
protected:
	RigidBody2D(ShapeType a_shape, glm::vec2 a_position, glm::vec2 a_velocity, float a_mass);
	// Might not be needed. Or may point to the center of the rigidbody.
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	// Nothing will act on this yet.
	float m_drag = 0.0f;
	float m_mass;
};

