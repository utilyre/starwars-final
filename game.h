#pragma once

#include <vector>
#include "vec2.h"
#include "enemy.h"
#include "player.h"

class Game
{
public:
    Game(int size);
    ~Game();

    void start();

private:
    int m_size;
    Player m_player;
    std::vector<Vec2> m_bullet_translations;
    std::vector<Enemy> m_enemies;

    void render() const;
    void integrate();
    bool input();

    void move_bullets();
    void move_enemies();
    void collide_bullets_with_enemies();
    void shoot();
};
