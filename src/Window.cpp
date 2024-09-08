#include "Window.h"
#include "Logger.h"
#include "chrono"

Window::Window(const char *title, int width, int height, bool fullscreen)
{
    SPDLOG_INFO("Criando Janela...");
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if (fullscreen)
    {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    }
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!window || !renderer)
    {
        SPDLOG_ERROR("Erro ao criar janela: {}", SDL_GetError());
        exit(1);
    }

    SPDLOG_INFO("Janela Criada com Sucesso!");

    camera = new SDL_Rect({0, 0, width, height});
    isopen = true;
}

void Window::clear()
{
    SDL_RenderClear(renderer);
}

void Window::update()
{
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_LSHIFT])
    {
        if (keystate[SDL_SCANCODE_UP]) {
            camera->y += 2;
        }
        if (keystate[SDL_SCANCODE_DOWN]) {
            camera->y -= 2;
        }
        if (keystate[SDL_SCANCODE_RIGHT]) {
            camera->x -= 2;
        }
        if (keystate[SDL_SCANCODE_LEFT]) {
            camera->x += 2;
        }
    }
    else
    {
        if (keystate[SDL_SCANCODE_UP])
        {
            camera->y += 1;
        }
        if (keystate[SDL_SCANCODE_DOWN])
        {
            camera->y -= 1;
        }
        if (keystate[SDL_SCANCODE_RIGHT])
        {
            camera->x -= 1;
        }
        if (keystate[SDL_SCANCODE_LEFT])
        {
            camera->x += 1;
        }
    }

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            close();
            break;

        case SDL_MOUSEWHEEL:
            if (event.wheel.y > 0)
            {
                scale*=1.1;
            }
            else
            {
                scale*=0.9;
            }
            break;

        default:
            break;
        }
    }
}

void Window::drawObjects(Physics *physics)
{
    SDL_RenderClear(renderer);
    for (PhysicsObject *object : physics->getObjects())
    {
        object->draw(this);
    }

    SDL_RenderPresent(renderer);
}

bool Window::isOpen()
{
    return isopen;
}

void Window::close()
{
    SDL_DestroyWindow(window);
    SDL_Quit();

    SPDLOG_INFO("Janela Fechando...");

    exit(0);
}

SDL_Renderer *Window::getRenderer()
{
    return renderer;
}
