#include <algorithm>
#include <ncurses.h>
#include <random>
#include <time.h>
#include "game.h"
#include "vec2.h"
#include "bullet.h"
#include "colorpairs.h"

Game::Game(int size) : m_size(size), m_player(3, Vec2(size - 1, size / 2))
{
    srand(time(0));

    initscr();
    start_color();
    noecho();
    curs_set(0);

    init_pair(CP_PLAYER, COLOR_BLUE, COLOR_BLACK);
    init_pair(CP_BULLET, COLOR_YELLOW, COLOR_BLACK);
    init_pair(CP_ENEMY, COLOR_RED, COLOR_BLACK);

    m_wstatus = newwin(3, 2 * size + 3, (LINES - size - 7) / 2, (COLS - 2 * size - 3) / 2);
    m_wgame = newwin(size + 2, 2 * size + 3, (LINES - size - 2) / 2, (COLS - 2 * size - 3) / 2);
}

Game::~Game()
{
    delwin(m_wgame);
    endwin();
}

void Game::start()
{
    spawn_enemy_randomly();

    while (true)
    {
        render();
        integrate();

        if (!input())
        {
            return;
        }
    }
}

void Game::render() const
{
    wclear(m_wstatus);
    box(m_wstatus, 0, 0);
    wclear(m_wgame);
    box(m_wgame, 0, 0);

    m_player.render(m_wstatus, m_wgame);

    for (Bullet bullet : m_bullets)
    {
        bullet.render(m_wgame);
    }

    for (Enemy enemy : m_enemies)
    {
        enemy.render(m_wgame);
    }

    wrefresh(m_wstatus);
    wrefresh(m_wgame);
}

void Game::integrate()
{
    move_bullets();
    move_enemies();
    collide_bullets_with_enemies();
}

bool Game::input()
{
    while (true)
    {
        switch (wgetch(m_wgame))
        {
        case 'q':
            return false;
        case ' ':
            shoot();
            return true;
        case 'a':
            shoot();
            m_player.move(Vec2(0, -1), Vec2(m_size - 1, 0), Vec2(m_size - 1, m_size - 1));
            return true;
        case 'd':
            shoot();
            m_player.move(Vec2(0, 1), Vec2(m_size - 1, 0), Vec2(m_size - 1, m_size - 1));
            return true;
        }
    }
}

void Game::spawn_enemy_randomly()
{
    const Enemy &blueprint = BP_ENEMIES[rand() % ENEMIES_LEN];
    Enemy enemy(blueprint, m_size);
    m_enemies.push_back(enemy);
}

void Game::move_bullets()
{
    for (auto it = m_bullets.begin(); it != m_bullets.end();)
    {
        Bullet &bullet = *it;
        bullet.move(Vec2(-1, 0));

        if (bullet.translation().y < 0)
        {
            it = m_bullets.erase(it);
            continue;
        }

        it++;
    }
}

void Game::move_enemies()
{
    for (auto it = m_enemies.begin(); it != m_enemies.end();)
    {
        Enemy &enemy = *it;
        enemy.move(Vec2(1, 0));

        if (enemy.bottom() >= m_size - 1)
        {
            it = m_enemies.erase(it);
            spawn_enemy_randomly();

            m_player.take_damage(1);
            if (m_player.is_dead())
            {
                // TODO: gameover
            }

            continue;
        }

        it++;
    }
}

void Game::collide_bullets_with_enemies()
{
    for (auto bullet_it = m_bullets.begin(); bullet_it != m_bullets.end();)
    {
        const Bullet &bullet = *bullet_it;

        bool should_erase_bullet = false;
        for (auto enemy_it = m_enemies.begin(); enemy_it != m_enemies.end();)
        {
            Enemy &enemy = *enemy_it;

            if (enemy.collides_with(bullet.translation()))
            {
                should_erase_bullet = true;
                enemy.take_damage(1);
                if (enemy.is_dead())
                {
                    enemy_it = m_enemies.erase(enemy_it);
                    spawn_enemy_randomly();
                }

                break;
            }

            enemy_it++;
        }

        if (should_erase_bullet)
        {
            bullet_it = m_bullets.erase(bullet_it);
            continue;
        }

        bullet_it++;
    }
}

void Game::shoot()
{
    m_bullets.emplace_back(Vec2(m_player.translation().y - 1, m_player.translation().x));
}
