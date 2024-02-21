#pragma once

#include <fstream>
#include <ncurses.h>
#include "rect.h"
#include "vec2.h"

/**
 * Represents the state of an enemy.
 */
class Enemy
{
public:
    Enemy();
    Enemy(int health, Vec2 size);
    Enemy(const Enemy &blueprint, int range_x);

    /**
     * Saves enemy state to `out` stream.
     */
    void save_to(std::ofstream &out) const;

    /**
     * Loads enemy state from `in` stream.
     */
    void load_from(std::ifstream &in);

    /**
     * Renders enemy onto `wgame` window.
     */
    void render(WINDOW *wgame) const;

    /**
     * Returns whether the enemy is dead or not.
     */
    bool is_dead() const;

    /**
     * Returns whether the enemy collides with `other` rectangle.
     */
    bool collides_with(Rect other) const;

    /**
     * Returns the amount of points player gains by destroying this enemy.s
     */
    int points() const;

    /**
     * Decreases enemy health by `amount`.I
    */
    void take_damage(int amount);

    /**
     * Moves the enemy along `dr` vector.
    */
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
