#include "RigidBody2D.h"


RigidBody2D::RigidBody2D(ShapeType a_shape, glm::vec2 a_position, glm::vec2 a_velocity,
	float a_mass) : PhysicsObject(a_shape)
{
	// Doing it this way will cause issues?
	m_shapeID = a_shape;
	m_position = a_position;
	m_velocity = a_velocity;
	m_mass = a_mass;
}

void RigidBody2D::ApplyForce(glm::vec2 a_force)
{
	m_velocity += a_force / m_mass;
}

void RigidBody2D::ApplyForceToActor(RigidBody2D* a_actor, glm::vec2 a_force)
{
	a_actor->ApplyForce(a_force);
	this->ApplyForce(-a_force);
}

void RigidBody2D::FixedUpdate(glm::vec2 a_gravity, float a_timeStep)
{
	ApplyForce(a_gravity * m_mass * a_timeStep);
	// Drag happens here. No drag variable.
	// m_velocity -= m_velocity * m_drag * a_timeStep;
	m_position += m_velocity * a_timeStep;
}



void RigidBody2D::ResolveCollision(RigidBody2D* a_actor, glm::vec2 a_collisionNormal)
{
	glm::vec2 normal = glm::normalize(a_collisionNormal);
	glm::vec2 relateiveVelocity = a_actor->GetVelocity() - m_velocity;

	// Need to add elasticity to compelete

	float j =
		glm::dot(-(1 + (m_elasticity * a_actor->m_elasticity)) * (relateiveVelocity), normal) 
		 /
		glm::dot(normal, normal * ((1 / m_mass) + (1 / a_actor->GetMass())));


	glm::vec2 force = normal * j;

	ApplyForceToActor(a_actor, force);

}