#ifndef COLLISION_H
#define COLLISION_H

#include "PhysicsObject.h"
#include "Box.h"
#include "CollisionResolution.h"

class Collision
{
public:
    void checkCollision(PhysicsObject *object1, PhysicsObject *object2);

private:
    bool checkBoxBoxCollision(Box* box1, Box* box2);
    bool checkLineCollision(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4);
};

#endif
