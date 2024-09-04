#include "Physics.h"

void Physics::addObject(PhysicsObject *object)
{
    objects.push_back(object);
}

void Physics::update(float deltaTime)
{
    for (PhysicsObject *object : objects)
    {
        if (object->isStatic())
            continue;
        object->applyForce({0, gravity});
    }

    for (PhysicsObject *object : objects)
    {
        if (object->isStatic())
            continue;
        object->update(deltaTime);
    }

    // TODO: Collision detection
}
