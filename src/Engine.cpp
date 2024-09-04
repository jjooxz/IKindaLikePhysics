#include "Engine.h"
#include "memory"
#include "chrono"
#include "Logger.h"

Engine::Engine(const char *title, int width, int height, bool fullscreen, float deltaTime, float gravity)
    : deltaTime(deltaTime), gravity(gravity)
{
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
    float frameLimit = 1.f / 60000.f;
    using clock = std::chrono::steady_clock;

    SPDLOG_INFO("Engine started");

    while (true)
    {

        auto frameStart = clock::now();

        physics->update(deltaTime);

        for (PhysicsObject *object : physics->getObjects())
        {
            object->draw();
        }

        Logger::instance().flush();

        auto frameEnd = clock::now();
        auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(frameStart - frameEnd);
        auto overhead = frameLimit - dt.count();
        if (overhead > 0)
            Sleep(overhead);
    }
}
