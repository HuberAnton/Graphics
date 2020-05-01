#pragma once

#include "PhysicsObject.h"


class RigidBody2D;

class Plane : public PhysicsObject
{
public:
	
	Plane(glm::vec2 a_normal, float a_distance = 0.0f);




	void SetNormal(glm::vec2& a_normal);
	glm::vec2 GetNormal() { return m_normal; }
	// Distance from center I suppose.
	void SetDistance(float a_distance) { m_distanceToOrigin = a_distance; }
	float GetDistance() { return m_distanceToOrigin; }

	void FixedUpdate(glm::vec2 a_gravity, float a_timestep) {};

	void ResolveCollision(RigidBody2D* a_other);

private:
	// Think of the normal the 'Up' of the plane.
	glm::vec2 m_normal = glm::vec2(0,1);
	float m_distanceToOrigin;

};

