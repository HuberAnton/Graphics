#pragma once
#include "RigidBody2D.h"


class AabbCollider2D : public RigidBody2D
{
public:
	AabbCollider2D(glm::vec2 a_position,
		glm::vec2 a_extents = glm::vec2(1.0f, 1.0f),
		glm::vec2 a_veloctiy = glm::vec2(0.0f),
		float a_mass = 1.0f);

	// This will work right?
	//glm::vec2 GetPosition() { return m_position; }
	//void SetPosition(glm::vec2& a_position) { m_position = a_position; }

	glm::vec2 GetExtents() { return m_extents; }
	void SetExtent(glm::vec2 a_extent) { m_extents = a_extent; }

	float GetWidth() { return m_extents.x; }
	float GetHeight() { return m_extents.y; }

	// Note that this will casue issues when not a perfect square.
	glm::vec2 GetMin() { return m_position - 0.5f * m_extents; }

	glm::vec2 GetMax() { return m_position + 0.5f * m_extents; }
	// Not needed.
	//bool CheckCollision(PhysicsObject* a_other) {return false;}
	
private:
	// I suppose the height and width will always be the same
	// Hence the union... I really should become comftorable to use them.
	// X width Y height.
	
	glm::vec2 m_extents;
	/*union extents
	{
		glm::vec2 extents:
		struct 
		{
			float m_width;
			float m_height;
		};
	};*/
};

