#include <algorithm>
#include <ncurses.h>
#include <random>
#include <time.h>
#include "game.h"
#include "vec2.h"

Game::Game(int size) : m_size(size), m_player(3, Vec2(size - 1, size / 2))
{
    srand(time(0));

    initscr();
    noecho();
    curs_set(0);

    m_wgame = newwin(size + 2, 2 * size + 3, 0, 0);
    refresh();
    box(m_wgame, 0, 0);
    wrefresh(m_wgame);
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
    for (int i = 0; i < m_size; i++)
    {
        for (int j = 0; j < m_size; j++)
        {
            mvwprintw(m_wgame, i + 1, 2 * j + 2, "-");
        }
    }

    m_player.render(m_wgame);

    for (Vec2 translation : m_bullet_translations)
    {
        mvwprintw(m_wgame, translation.y + 1, 2 * translation.x + 2, "^");
    }

    for (Enemy enemy : m_enemies)
    {
        enemy.render(m_wgame);
    }
}

void Game::integrate()
{
    move_bullets();
    collide_bullets_with_enemies();
    move_enemies();
}

bool Game::input()
{
    while (true)
    {
        switch (wgetch(m_wgame))
        {
        case 'q':
            return false;
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
    for (auto it = m_bullet_translations.begin(); it != m_bullet_translations.end();)
    {
        Vec2 &translation = *it;
        translation.y--;

        if (translation.y < 0)
        {
            it = m_bullet_translations.erase(it);
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
    for (auto it = m_enemies.begin(); it != m_enemies.end();)
    {
        Enemy &enemy = *it;

        bool should_erase_enemy = false;
        for (auto it = m_bullet_translations.begin(); it != m_bullet_translations.end();)
        {
            Vec2 &bullet_translation = *it;

            if (bullet_translation.y >= enemy.top() && bullet_translation.y <= enemy.bottom() &&
                bullet_translation.x >= enemy.left() && bullet_translation.x <= enemy.right())
            {
                enemy.take_damage(1);
                it = m_bullet_translations.erase(it);

                if (enemy.is_dead())
                {
                    should_erase_enemy = true;
                    break;
                }
            }
            else
            {
                it++;
            }
        }

        if (should_erase_enemy)
        {
            it = m_enemies.erase(it);
            spawn_enemy_randomly();
        }
        else
        {
            it++;
        }
    }
}

void Game::shoot()
{
    m_bullet_translations.emplace_back(m_player.translation().y - 1, m_player.translation().x);
}
