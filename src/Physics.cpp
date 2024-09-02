#include "Physics.h"

void Physics::addObject(PhysicsObject* object) {
    objects.push_back(object);
}

void Physics::update(float deltaTime) {
    for (PhysicsObject* object : objects) {
        object->applyForce({0, gravity});
    }

    for (PhysicsObject* object : objects) {
        object->update(deltaTime);
    }

    //TODO: Collision detection
}