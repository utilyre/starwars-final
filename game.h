#pragma once

#include <vector>
#include <ncurses.h>
#include <fstream>
#include "vec2.h"
#include "enemy.h"
#include "bullet.h"
#include "player.h"
#include "menu.h"

/**
 * Represents the state of the entire game.
 */
class Game
{
public:
    Game();
    Game(int size, int max_score);
    ~Game();

    /**
     * Starts the game loop.
     */
    void start();

    /**
     * Stops the game loop.
     */
    void stop();

private:
    int m_size;
    WINDOW *m_wstatus;
    WINDOW *m_wgame;

    int m_max_score;
    Player m_player;
    std::vector<Bullet> m_bullets;
    std::vector<Enemy> m_enemies;

    bool m_already_won;
    bool m_stopped;

    /**
     * Saves the game state to a file.
     */
    void save() const;

    /**
     * Loads the game state from a file.
     */
    void load();

    /**
     * Resets the game state.
     */
    void reset();

    /**
     * Renders the game on the screen based on its state.
     */
    void render() const;

    /**
     * Updates game's state.
     */
    void integrate();

    /**
     * Takes user input and handles it.
     */
    bool input();

    /**
     * Checks whether the game has ended by the player winning and displays the win menu.
     */
    void check_win();

    /**
     * Checks whether the game has ended by the player losing and displays the gameover menu.
     */
    void check_gameover();

    /**
     * Moves bullets upwards.
     */
    void move_bullets();

    /**
     * Moves enemies downwards.
     */
    void move_enemies();

    /**
     * Checks Bullet-Enemy collision and deals damage to enemies.
     */
    void collide_bullets_with_enemies();

    /**
     * Spawns a single enemy randomly on the screen.
     */
    void spawn_enemy_randomly();

    /**
     * Shoots a bullet from player.
     */
    void shoot();
};
