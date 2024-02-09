#pragma once

#include "vec2.h"

class Game
{
public:
    Game(int size, Vec2 player_translation);
    ~Game();

    void start();

private:
    int m_size;
    Vec2 m_player_translation;

    void render() const;
    void move_player(int dy, int dx);
};
