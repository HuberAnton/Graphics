#pragma once
#include "CircleColider.h"
#include "Plane.h"
#include "AabbCollider2D.h"

// Handles all collisions.
// Any extra rules shoudle be added here


class CollisionManager
{
public:
	static glm::vec2 CircleVCircle(PhysicsObject* a_circle1, PhysicsObject* a_circle2);

	static glm::vec2 AabbvAabb(PhysicsObject* a_aabb1, PhysicsObject* a_aabb2);

	static glm::vec2 PlanevPlane(PhysicsObject* a_plane1, PhysicsObject* a_plane2);

	static glm::vec2 AabbvCircle(PhysicsObject* a_aabb, PhysicsObject* a_circle);

	static glm::vec2 CirclevAaabb(PhysicsObject* a_circle, PhysicsObject* a_aabb);

	static glm::vec2 CirclevPlane(PhysicsObject* a_circle, PhysicsObject* a_plane);

	static glm::vec2 PlanevCircle(PhysicsObject* a_plane, PhysicsObject* a_circle);

	static glm::vec2 AabbvPlane(PhysicsObject* a_aabb, PhysicsObject* a_plane);

	static glm::vec2 PlanevAabb(PhysicsObject* a_plane, PhysicsObject* a_aabb);

private:
	static glm::vec2 clamp(glm::vec2& a_vec2, glm::vec2& a_min, glm::vec2& a_max);

};



