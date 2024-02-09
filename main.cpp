#include "game.h"
#include "vec2.h"

int main()
{
    int size = 20;
    Game game(size, Vec2(size - 1, size / 2));

    game.start();
}
