#include "CollisionManager.h"
#include <cmath>

#include "AabbCollider2D.h"
#include "CircleColider.h"
// Collision rules.
#include <iostream>

glm::vec2 CollisionManager::CircleVCircle(PhysicsObject* a_circle1, PhysicsObject* a_circle2)
{

	CircleColider* c1 = dynamic_cast<CircleColider*>(a_circle1);
	CircleColider* c2 = dynamic_cast<CircleColider*>(a_circle2);

	// Gets the distance from center points
	glm::vec2 dispalcment = (c1->GetPosition() - c2->GetPosition());
	// Gets the combined size of circles from center to outside
	float radii = c1->GetRadius() + c2->GetRadius();

	float overlap = (radii)-glm::length(dispalcment);
	// If overlap is a positive number they are overlapping
	if (overlap > 0.0f)
	{
		return glm::normalize(dispalcment) * overlap;
	}
	// No overlap.
	return glm::vec2(0.0f);
}

glm::vec2 CollisionManager::AabbvAabb(PhysicsObject* a_aabb1, PhysicsObject* a_aabb2)
{
	AabbCollider2D* b1 = dynamic_cast<AabbCollider2D*>(a_aabb1);
	AabbCollider2D* b2 = dynamic_cast<AabbCollider2D*>(a_aabb2);

	
	float maxOverlap = 10000000.0f;
	// It looks like this was done to not use magic numbers.
	// Could change the above to a #define
	float overlap = maxOverlap; 

	glm::vec2 overlapVector = glm::vec2(0.0f);


	// X axis
	if (b1->GetMax().x > b2->GetMin().x)
	{
		// overlap for this side
		float localOverlap = abs(b1->GetMax().x - b2->GetMin().x);
		if (localOverlap < overlap)
		{
			overlap = localOverlap;
			overlapVector = glm::vec2(-overlap, 0);
		}
	}
	else
	{
		return glm::vec2(0.0f);
	}

	if (b1->GetMin().x < b2->GetMax().x)
	{
		float localOverlap = abs(b1->GetMin().x - b2->GetMax().x);
		if (localOverlap < overlap)
		{
			overlap = localOverlap;
			overlapVector = glm::vec2(overlap, 0);
		}
	}
	else
	{
		return glm::vec2(0.0f);
	}


	// Y axis

	if (b1->GetMax().y > b2->GetMin().y)
	{
		// overlap for this side
		float localOverlap = abs(b1->GetMax().y - b2->GetMin().y);
		if (localOverlap < overlap)
		{
			overlap = localOverlap;
			overlapVector = glm::vec2(0, -overlap);
		}
	}
	else
	{
		return glm::vec2(0.0f);
	}

	if (b1->GetMin().y < b2->GetMax().y)
	{
		float localOverlap = abs(b1->GetMin().y - b2->GetMax().y);
		if (localOverlap < overlap)
		{
			overlap = localOverlap;
			overlapVector = glm::vec2(0, overlap);
		}
	}
	else
	{
		return glm::vec2(0.0f);
	}
	
	return overlapVector;
}

glm::vec2 CollisionManager::PlanevPlane(PhysicsObject* a_plane1, PhysicsObject* a_plane2)
{
	// Should never collide... Well... Floors are static otherwise it's aabb?
	return glm::vec2(0.0f);
}

// Works very similar to the circle v circle but with added steps.
glm::vec2 CollisionManager::AabbvCircle(PhysicsObject* a_aabb, PhysicsObject* a_circle)
{
	AabbCollider2D* b = dynamic_cast<AabbCollider2D*>(a_aabb);
	CircleColider* c = dynamic_cast<CircleColider*>(a_circle);

	
	glm::vec2 clampedCenter = glm::clamp(c->GetPosition(), b->GetMin(), b->GetMax());


	glm::vec2 displacement = clampedCenter - c->GetPosition();
	float overlap = c->GetRadius() - glm::length(displacement);

	if (overlap > 0.0f)
	{
		return glm::normalize(displacement) * overlap;
	}
	return glm::vec2(0.0f);
}

glm::vec2 CollisionManager::CirclevAaabb(PhysicsObject* a_circle, PhysicsObject* a_aabb)
{
	return AabbvCircle(a_aabb, a_circle);
}

glm::vec2 CollisionManager::CirclevPlane(PhysicsObject* a_circle, PhysicsObject* a_plane)
{
	CircleColider* c = dynamic_cast<CircleColider*>(a_circle);
	Plane* l = dynamic_cast<Plane*>(a_plane);

	// I need to look over this some more.
	float positionDotNormal = glm::dot(c->GetPosition(), l->GetNormal());

	float distance = positionDotNormal - (l->GetDistance() + c->GetRadius());

	if (distance < 0.0f)
	{
		return -(l->GetNormal()) * distance;
	}
	else
	{
		return glm::vec2(0.0f);
	}
}

glm::vec2 CollisionManager::PlanevCircle(PhysicsObject* a_plane, PhysicsObject* a_circle)
{
	/* Might have to add a (-) to the return*/ return CirclevPlane(a_circle, a_plane);
}

glm::vec2 CollisionManager::AabbvPlane(PhysicsObject* a_aabb, PhysicsObject* a_plane)
{
	AabbCollider2D* b = dynamic_cast<AabbCollider2D*>(a_aabb);
	Plane* l = dynamic_cast<Plane*>(a_plane);

	glm::vec2 extents = 0.5f * b->GetExtents();
	// Need to read up a lil more about the below . Probably a mathy thing
	glm::vec2 extentsNegX = 0.5f * glm::vec2(-b->GetExtents().x, b->GetExtents().y);

	float dotExtents = glm::dot(extents, l->GetNormal());
	float dotExtentsNegX = glm::dot(extentsNegX, l->GetNormal());

	// So creates a circle out of the data then does the circle line call. Neat

	float radius = fmaxf(fabs(dotExtents), fabsf(dotExtentsNegX));

	CircleColider projection(b->GetPosition(), glm::vec2(0.0f), b->GetMass(), radius);
	// Not completed.
	return CirclevPlane(&projection, a_plane);
}

glm::vec2 CollisionManager::PlanevAabb(PhysicsObject* a_plane, PhysicsObject* a_aabb)
{
	return AabbvPlane(a_aabb, a_plane);
}


glm::vec2 clamp(glm::vec2& a_vec2, glm::vec2& a_min, glm::vec2& a_max)
{
	return { fminf(fmaxf(a_vec2.x, a_min.x), a_max.x),
				fminf(fmaxf(a_vec2.y, a_min.y), a_max.y) };
}