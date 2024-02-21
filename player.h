#pragma once

#include <ncurses.h>
#include <fstream>
#include "vec2.h"

/**
 * Represents the state of a player.
 */
class Player
{
public:
    Player();
    Player(int health, Vec2 translation);

    /**
     * Saves the player state into `out` stream.
     */
    void save_to(std::ofstream &out) const;

    /**
     * Loads the player state from `in` stream.
     */
    void load_from(std::ifstream &in);

    /**
     * Renders the player onto `wgame` window.
     */
    void render(WINDOW *wgame) const;

    /**
     * Returns whether the player is dead or not.
     */
    bool is_dead() const;

    /**
     * Returns the current health of the player.
     */
    int health() const;

    /**
     * Returns the current score of the player.
     */
    int score() const;

    /**
     * Returns the current translation of the player.
     */
    Vec2 translation() const;

    /**
     * Decreases player health by `amount`.
     */
    void take_damage(int amount);

    /**
     * Increases the player score by `amount`.
     */
    void take_score(int amount);

    /**
     * Moves the player along `dr` and confines movement within `min` and `max`.
     */
    void move(Vec2 dr, Vec2 min, Vec2 max);

private:
    int m_health;
    int m_score;
    Vec2 m_translation;
};
