#ifndef COLLISION_RESOLUTION_H
#define COLLISION_RESOLUTION_H

#include "Objects.h"

class CollisionResolution
{
public:
    static void ResolveCollisionBoxBox(Box* box1, Box* box2);
};

#endif