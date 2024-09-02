#include "Engine.h"

Engine::Engine(const char *title, int width, int height, bool fullscreen = false, float deltaTime = 1.0f / 60.0f, float gravity = -9.8f) : deltaTime(deltaTime), gravity(gravity)
{
    /*
    Window Config:
    @param title - The title of the window
    @param width - The width of the window
    @param height - The height of the window
    @param fullscreen - Whether the window should be fullscreen
    Simulation Config:
    @param deltaTime - The time between each frame
    @param gravity - The gravity of the simulation
    */

    // TODO: Create window
    // window = new Window(title, width, height, fullscreen);

    physics = new Physics(gravity);
}

void Engine::addObject(PhysicsObject *object)
{
    physics->addObject(object);
}

void Engine::start()
{
    while (true)
    {
        physics->update(deltaTime);
    }
}