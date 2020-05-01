#pragma once

#include "glm.hpp"

// Why the char? Is it so it is treated like
// a char? Inheritance right?
enum class ShapeType : char
{
	AABOX,
	SPHERE,
	PLANE,
	ShapeCount
};

class PhysicsObject
{
public:
	PhysicsObject(ShapeType a_shapeType) { m_shapeID = a_shapeType; }
	virtual void FixedUpdate(glm::vec2 gravity, float m_timestep) = 0;
	// Make gizmo exitst here.
	// so it can be drawn.
	virtual void resetPosition() {};
	ShapeType GetShape() { return m_shapeID; }


	// If true skips update in PhysicsScene and does not move if things collide 
	bool m_static = false;
	float m_elasticity = 1.0f;
protected:
	ShapeType m_shapeID;
	// Might need a reference to it's actual object.
};

