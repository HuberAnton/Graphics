#include "Plane.h"
#include "RigidBody2D.h"

//Plane::Plane() : PhysicsObject(ShapeType::PLANE)
//{
//	m_normal = glm::vec2(0, 1);
//	m_distanceToOrigin = 0;
//}

Plane::Plane(glm::vec2 a_normal, float a_distance) : 
	m_normal(a_normal), m_distanceToOrigin(a_distance),
	PhysicsObject(ShapeType::PLANE)
{
	// Why though?
	SetNormal(m_normal);
}


void Plane::SetNormal(glm::vec2& a_normal)
{
	// I mean technicly if it's greater then 0?
	if (glm::length(a_normal) <= 0.0f)
	{

	}
	else
	{
		m_normal = glm::normalize(a_normal);
	}
}

void Plane::ResolveCollision(RigidBody2D* a_other)
{
	glm::vec2 relativeVel = a_other->GetVelocity();

	float j =
		glm::dot(-(1 + (m_elasticity * a_other->m_elasticity)) * (relativeVel), m_normal)
		/
		glm::dot(m_normal, m_normal * (1 / a_other->GetMass()));

	glm::vec2 force = m_normal * j;

	a_other->ApplyForce(force);
}


