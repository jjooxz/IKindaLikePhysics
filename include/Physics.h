#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>
#include "PhysicsObject.h"

class Physics
{
public:
    Physics(float gravity) : gravity(gravity) {}

    void addObject(PhysicsObject *object);

    void update(float deltaTime);

    auto getObjects() { return objects; }

private:
    float gravity;
    std::vector<PhysicsObject*> objects;
    
};

#endif // PHYSICS_H
