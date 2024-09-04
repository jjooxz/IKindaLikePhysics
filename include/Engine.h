#ifndef ENGINE_H
#define ENGINE_H

#include "Physics.h"

class Engine
{
public:
    /*
        @return The physics engine object
        @param title - The title of the window
        @param width - The width of the window
        @param height - The height of the window
        @param fullscreen - Whether the window should be fullscreen
        @param fps - Frames per second
        @param deltaTime - The time between each frame
        @param gravity - The gravity of the simulation
    */
    Engine(const char *title, int width, int height, bool fullscreen = false, float deltaTime = 1.0f / 60.0f, float gravity = -9.8f);

    void addObject(PhysicsObject *object);

    void start();

private:
    Physics *physics;
    float deltaTime, gravity;
    // Window* window;
};

#endif
