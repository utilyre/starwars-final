#pragma once

#include <vector>
#include <ncurses.h>
#include "vec2.h"
#include "enemy.h"
#include "bullet.h"
#include "player.h"

class Game
{
public:
    Game(int size);
    ~Game();

    void start();

private:
    int m_size;
    WINDOW *m_wstatus;
    WINDOW *m_wgame;

    Player m_player;
    std::vector<Bullet> m_bullets;
    std::vector<Enemy> m_enemies;

    void render() const;
    void integrate();
    bool input();

    void move_bullets();
    void move_enemies();
    void collide_bullets_with_enemies();
    void spawn_enemy_randomly();
    void shoot();
};
