#include "Engine.h"
#include "memory"
#include "chrono"
#include "Logger.h"

using namespace std::chrono_literals;

Engine::Engine(const char *title, int width, int height, bool fullscreen, float deltaTime, float gravity)
    : deltaTime(deltaTime), gravity(gravity)
{
    Logger::instance().flush();
    window = new Window(title, width, height, fullscreen);
    collision = new Collision();
    physics = new Physics(gravity);
}

void Engine::addObject(PhysicsObject *object)
{
    physics->addObject(object);
}

void Engine::start()
{
    using clock = std::chrono::high_resolution_clock;
    float frameLimit = 450.0f / 60.0f; // 1000 milliseconds / 60 FPS = 16.67 ms per frame

    SPDLOG_INFO("Engine started");

    while (true)
    {
        auto frameStart = clock::now();

        window->update();

        // Atualiza a física, que deve incluir a aplicação da gravidade
        physics->update(deltaTime);

        // Verifica colisões entre objetos
        auto objects = physics->getObjects();
        size_t numObjects = objects.size();

        for (size_t i = 0; i < numObjects; ++i)
        {
            for (size_t j = i + 1; j < numObjects; ++j)
            {
                collision->checkCollision(objects[i], objects[j]);
            }
        }

        Logger::instance().flush();

        // Desenha os objetos na tela
        window->drawObjects(physics);

        auto frameEnd = clock::now();
        auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart).count();
        auto overhead = frameLimit - dt;

        if (overhead > 0)
        {
            Sleep(static_cast<int>(overhead));
        }
    }
}

void Engine::Sleep(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }
