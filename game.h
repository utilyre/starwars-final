#pragma once

#include <vector>
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
    std::vector<Vec2> m_bullet_translations;

    void render() const;
    void integrate();
    void move_player(int dy, int dx);
    void shoot();
};
