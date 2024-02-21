#pragma once

#include <ncurses.h>
#include <fstream>
#include "vec2.h"

/**
 * Represents a bullet shot from the player.
 */
class Bullet
{
public:
    Bullet();
    Bullet(Vec2 translation);

    /**
     * Saves the bullet state into `out` stream.
     */
    void save_to(std::ofstream &out) const;

    /**
     * Loads bullet state from `in` stream.
     */
    void load_from(std::ifstream &in);

    /**
     * Renders the bullet on `wgame` window.
     */
    void render(WINDOW *wgame) const;

    /**
     * Returns the current translation of the bullet.
     */
    Vec2 translation() const;

    /**
     * Moves the bullet along `dr` vector.
     */
    void move(Vec2 dr);

private:
    Vec2 m_translation;
};
