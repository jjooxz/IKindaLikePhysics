#define SDL_MAIN_HANDLED
#include "Engine.h"
#include "Box.h"

Box* box;
Box* chao;

int main()
{
    box = new Box(Vector2(0,0), Vector2(0,0), 1.0f, 100.0f, 100.0f, 0, false, {255, 255, 255, 255});
    chao = new Box(Vector2(-100, -200), Vector2(0, 0), 1.0f, 1000.0f, 40.0f, 3, true, {255, 255, 255, 255});
    // Inicialização do engine e adição do box
    // optimal delta time : 1.0f / 60.0f
    Engine engine("I Kinda Like Physics", 800, 600, false, 1.0f / 60.0f, -9.8f);
    engine.addObject(box);
    engine.addObject(chao);

    // Início da execução do engine
    engine.start();

    return 0;
}
