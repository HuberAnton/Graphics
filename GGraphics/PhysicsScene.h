#pragma once

#include "PhysicsObject.h"
#include "glm.hpp"
#include <vector>
#include <algorithm>
#include "CollisionManager.h"
#include "Object.h"
#include <functional>
using collisionFunction = std::function<glm::vec2(PhysicsObject*, PhysicsObject*)>;

// I'm straight up following the tuts for this
// I probably can use osme of what I've already laid out to help this
// Like an object can have a component 'physics' added to it.
// How would you then attach that peice to it without every object
// having a variable? Inheritance maybe?
// All textures, materials, rigidboies ect all inherit from a component class?
// I don't think that would work...



class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();

	// I might need to change this to actors.
	void AddActor(Object* a_object);
	void RemoveActor(Object* a_object);

	void Update(float a_deltaTime);
	// The tut has an update gizmos... I'll have to see what it does
	// Apparetly it is the draw call for the gizmos in their new positions.
	// So the objects in here also need to exist in the obj manager to be drawn.

	// Might be needed if the rigidbody has an offset.
	void ApplyPositionToObj(Object* a_actor, RigidBody2D* a_rigidBody);

	void SetTimeStep(float a_timestep) { m_timeStep = a_timestep; }
	void SetGravity(glm::vec2 a_gravity) { m_gravity = a_gravity; }
protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<Object*> m_actors;
	float m_accumulatedTime = 0.0f;

	// Remember THIS std::function<glm::vec2(PhysicsObject*, PhysicsObject*)>;
	// is the type
	static collisionFunction m_collisionFunctions[];
};

