#include "AabbCollider2D.h"


AabbCollider2D::AabbCollider2D(glm::vec2 a_position,
	glm::vec2 a_extents /*= glm::vec2(1.0f)*/,
	glm::vec2 a_veloctiy /*= glm::vec2(0.0f)*/,
	float a_mass /*= 1.0f)*/) : RigidBody2D(ShapeType::AABOX, a_position, a_veloctiy, a_mass)
{
	m_extents.x = a_extents.x;
	m_extents.y = a_extents.y;
}


