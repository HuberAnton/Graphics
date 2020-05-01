#include "CircleColider.h"

// Does this cpp need to exist? Yes it does.

// Note that the tutorial create
CircleColider::CircleColider(glm::vec2 a_position, glm::vec2 a_velocity,
	float a_mass, float a_radius) : RigidBody2D(ShapeType::SPHERE, a_position, a_velocity, a_mass)
	, m_radius(a_radius) {}


// This is just placeholder I imagine till the collision manager is added.
//bool CircleColider::CheckCollision(PhysicsObject* a_actor)
//{
//	// Needs checking if success
//	CircleColider* other  = dynamic_cast<CircleColider*>(a_actor);
//	return false;
//}
