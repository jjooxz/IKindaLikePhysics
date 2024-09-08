#ifndef WINDOW_H
#define WINDOW_H

#include "Physics.h"
#include "SDL2/SDL.h"

class Window
{
public:
    Window(const char *title, int width, int height, bool fullscreen);
    ~Window();

    void clear();
    void update();
    bool isOpen();
    void close();
    void drawObjects(Physics *physics);
    SDL_Renderer *getRenderer();
    SDL_Rect *camera;
    float scale = 1.0f;

    int getWidth() {
        int w, h;
        SDL_GetWindowSize(window, &w, &h);
        return w;
    }

    int getHeight() {
        int w, h;
        SDL_GetWindowSize(window, &w, &h);
        return h;
    }

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool isopen = false;
};

#endif