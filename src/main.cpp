#include "Engine.h"
#include "Box.h"

Box* box;

int main()
{
    box = new Box(Vector2(0,0), Vector2(0,0), 1.0f, 100.0f, 100.0f);
    // Inicialização do engine e adição do box
    Engine engine("I Kinda Like Physics", 800, 600, true, 1.0f / 60.0f, -9.8f);
    engine.addObject(box);

    // Início da execução do engine
    engine.start();

    return 0;
}
