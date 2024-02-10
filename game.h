#pragma once

#include <vector>
#include "vec2.h"
#include "enemy.h"

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
    std::vector<Enemy> m_enemies;

    void render() const;
    void integrate();
    bool input();

    void move_player(int dy, int dx);
    void shoot();
};
