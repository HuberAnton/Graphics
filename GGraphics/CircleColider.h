#pragma once

#include "glm.hpp"
#include "RigidBody2D.h"



class CircleColider : public RigidBody2D
{
public:
	CircleColider(glm::vec2 a_position, glm::vec2 a_velocity,
		float a_mass, float a_radius);
	

	// Probably not needed.
	//virtual bool CheckCollision(PhysicsObject* a_actor);

	float GetRadius() { return m_radius; }
	// I can not think of a time when doing this will not require a new mesh.
	//void SetRadius(float a_radius);


protected:
	float m_radius;
};



// 2 Things that need to be done... maybe 3.
// Add rigidbodies and all their needed parts to objects.
// Pass in objects to the fixed update and make sure correct parts are called.
// Make sure the physics object has a transfrom as well as the actual object and add them together


// Another thing...
// I could probably make an update for each object that includes the fixed update as well as the regular update.
// Would be done in the object manager.
