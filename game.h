#pragma once

#include <vector>
#include <ncurses.h>
#include <fstream>
#include "vec2.h"
#include "enemy.h"
#include "bullet.h"
#include "player.h"

#define CP_PLAYER 1
#define CP_BULLET 2
#define CP_ENEMY 3

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

    void save() const;
    // void load();

    void render() const;
    void integrate();
    bool input();

    void move_bullets();
    void move_enemies();
    void collide_bullets_with_enemies();
    void spawn_enemy_randomly();
    void shoot();
};
