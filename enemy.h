#pragma once

#include <fstream>
#include <ncurses.h>
#include "rect.h"
#include "vec2.h"

class Enemy
{
public:
    Enemy(int health, Vec2 size);
    Enemy(const Enemy &blueprint, int range_x);

    void save_to(std::ofstream &out) const;

    void render(WINDOW *wgame) const;

    bool is_dead() const;
    bool collides_with(Rect other) const;
    int points() const;

    void take_damage(int amount);
    void move(Vec2 dr);

private:
    int m_health;
    Rect m_collision;
};

#define ENEMIES_LEN 4
const Enemy BP_ENEMIES[ENEMIES_LEN] = {
    Enemy(1, Vec2(1, 1)),
    Enemy(2, Vec2(2, 2)),
    Enemy(4, Vec2(3, 3)),
    Enemy(6, Vec2(4, 4)),
};
