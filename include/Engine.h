#ifndef ENGINE_H
#define ENGINE_H

#include "Physics.h"

class Engine
{
public:
    Engine(const char *title, int width, int height, bool fullscreen = false, float deltaTime = 1.0f / 60.0f, float gravity = -9.8f);

    void addObject(PhysicsObject *object);

    void start();

private:
    Physics *physics;
    float deltaTime, gravity;
    // Window* window;
};

#endif