#include "PhysicsScene.h"
#include "RigidBody2D.h"
#include <list>


// I'm gonna be straight up and admit I need to learn this proper.
// Using collisionFunction = std::function<glm::vec2(PhysicsObject*, PhysicsObject*)>
// So std::function declares a fuction pointer.
// So an array of function pointers that take in 2 physics objects each.
// Why glm::vec2? Is it just so you don't need to create a new data type that passes the
// physiscs objects? Probably. Oh it's templated so you can't template 2 types?
collisionFunction PhysicsScene::m_collisionFunctions[] =
{
    CollisionManager::AabbvAabb,
    CollisionManager::AabbvCircle,
    CollisionManager::AabbvPlane,
    CollisionManager::CirclevAaabb,
    CollisionManager::CircleVCircle,
    CollisionManager::CirclevPlane,
    CollisionManager::PlanevAabb,
    CollisionManager::PlanevCircle,
    CollisionManager::PlanevPlane
};




PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0.0f, 0.0f))
{

}

// This should always be a thing done at the end.
// Never a case when it shouldn't.
// Actually if an object gets deleted then it needs 
// to clean itself up as well...
// Problem for future me.
PhysicsScene::~PhysicsScene()
{
    //for (auto act : m_actors)
    //{
    //    delete act;
    //}
}

void PhysicsScene::AddActor(Object* a_object)
{
	m_actors.push_back(a_object);
}

void PhysicsScene::RemoveActor(Object* a_object)
{
	auto position = std::find(m_actors.begin(), m_actors.end(), a_object);
	m_actors.erase(position);
	delete a_object;
	a_object = nullptr;
}



// Comment this

void PhysicsScene::Update(float a_deltaTime)
{
    m_accumulatedTime += a_deltaTime;

    while (m_accumulatedTime >= m_timeStep)
    {
        for (Object* object : m_actors)
        {
            if (object->GetPhysicsObject()->GetShape() != ShapeType::PLANE)
            {
                object->FixedUpdate(m_gravity, m_timeStep);
                ApplyPositionToObj(object, (RigidBody2D*)object->GetPhysicsObject());
            }
        }
            // Keeps track of time passed between steps accuratly.
            m_accumulatedTime -= m_timeStep;
    }
  

    // An optimization? Good practice I suppose.
    int objectCount = (int)m_actors.size();


    // Loops through all physics objects and checks if colliding.
    // Then does physiscs.
    // More objects means it takes more time.
    for (int outer = 0; outer < objectCount - 1; outer++)
    {
        for (int inner = outer + 1; inner < objectCount; inner++)
        {
            // Get the physicsObjects from the game object. 
            PhysicsObject* actor1 = m_actors[outer]->GetPhysicsObject();
            PhysicsObject* actor2 = m_actors[inner]->GetPhysicsObject();
            
            // Get the shape of the collider on it.
            ShapeType shape1 = actor1->GetShape();
            ShapeType shape2 = actor2->GetShape();

            // Use cool math to get the correct function.
            // Note that the functions are stored in an array 
            int functionId = (int(shape1) * int(ShapeType::ShapeCount)) + int(shape2);
            collisionFunction collisionFunctionPtr = m_collisionFunctions[functionId];
            if (collisionFunctionPtr != nullptr)
            {
                // Calls the functions in CollisionMangager
                auto result = collisionFunctionPtr(actor1, actor2);
                // If a collision is detected.
                if (glm::length(result) > 0.001)
                {
                    // Cast both to rigid bodies to check if they move.
                    // If 1 doesn't have a rigidbody (ie; r1 == null) 
                    // then only r2 needs a reaction.
                    RigidBody2D* r1 = dynamic_cast<RigidBody2D*>(actor1);
                    RigidBody2D* r2 = dynamic_cast<RigidBody2D*>(actor2);
                    // Nore that this is to check if there is a rigidbody to move.
                    // It is the seperation of collider and rigidbody.
                    // If both exist then 2 moving objects
                    if (r1 && r2)
                    {
                        r1->SetPosition(r1->GetPosition() + 0.5f * result);
                        r2->SetPosition(r2->GetPosition() - 0.5f * result);
                        r1->ResolveCollision(r2, result);
                        ApplyPositionToObj(m_actors[outer], r1);
                        ApplyPositionToObj(m_actors[inner], r2);
                    }
                    else if (r1)
                    {
                        r1->SetPosition(r1->GetPosition() + result);
                        Plane* l = dynamic_cast<Plane*>(actor2);
                        l->ResolveCollision(r1);
                        //ApplyPositionToObj(m_actors[outer], r1);
                    }
                    else if (r2)
                    {
                        r2->SetPosition(r2->GetPosition() + result);
                        Plane* l = dynamic_cast<Plane*>(actor1);
                        l->ResolveCollision(r2);
                        ApplyPositionToObj(m_actors[inner], r2);
                    }
                }
                
            }
            else
            {
                std::cout << "Something went wrong with function pointers." << std::endl;
                system("pause");
            }
        }
    }


    // Now we have a regular update that occurs
    // for objects that are moving not due to physics
    // Animations maybe? translations?
   
    
    // This was from adam discussion
    
    // Update - order not important since fixed happens after set amount of time.

    // Draw the shapes multiple - This is using the same vbo and then drawing it in the correct position
    // So 3 cubes in 3 different places is actually the same cube drawn 3 times in the different locations.
    // Honesly almost there. Need to pass references to objects and modfiy the system add system slightly for the
    // managers.
    

}

// I have no idea if this works.
// Shenanigans that really are not fun or cool.
void PhysicsScene::ApplyPositionToObj(Object* a_actor, RigidBody2D* a_rigidBody)
{
    a_actor->SetPosition(glm::vec3(a_rigidBody->GetPosition(), 0));
}