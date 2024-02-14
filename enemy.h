#pragma once

#include <ncurses.h>
#include "vec2.h"

class Enemy
{
public:
    Enemy(int health, Vec2 size, Vec2 translation);

    void render(WINDOW *wgame) const;
    Vec2 size() const;
    int left() const;
    int top() const;
    int right() const;
    int bottom() const;

    void set_translation(Vec2 translation);
    void move(Vec2 dr);
    void take_damage();
    bool is_dead() const;

private:
    int m_health;
    Vec2 m_size;
    Vec2 m_translation;
};

#define ENEMIES_LEN 4
const Enemy ENEMIES[ENEMIES_LEN] = {
    Enemy(1, Vec2(1, 1), Vec2()),
    Enemy(2, Vec2(2, 2), Vec2()),
    Enemy(4, Vec2(3, 3), Vec2()),
    Enemy(6, Vec2(4, 4), Vec2()),
};
