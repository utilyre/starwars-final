#include <algorithm>
#include <ncurses.h>
#include "game.h"
#include "vec2.h"

Game::Game(int size) : m_size(size), m_player(Vec2(size - 1, size / 2))
{
    initscr();
    noecho();
    curs_set(0);

    // for test
    Enemy e = {
        .size = Vec2(2, 2),
        .translation = Vec2(3, 8),
        .health = 1,
    };
    m_enemies.push_back(e);
}

Game::~Game()
{
    endwin();
}

void Game::start()
{
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
            mvprintw(i, 2 * j + 1, "-");
        }
    }

    m_player.render();

    for (Vec2 translation : m_bullet_translations)
    {
        mvprintw(translation.y, 2 * translation.x + 1, "^");
    }

    for (Enemy enemy : m_enemies)
    {
        for (int i = 0; i < enemy.size.y; i++)
        {
            for (int j = 0; j < enemy.size.x; j++)
            {
                mvprintw(enemy.translation.y + i, 2 * (enemy.translation.x + j) + 1, "*");
            }
        }
    }
}

void Game::integrate()
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

    for (auto it = m_enemies.begin(); it != m_enemies.end();)
    {
        Enemy &enemy = *it;
        enemy.translation.y++;

        if (enemy.translation.y + enemy.size.y + 1 > m_size)
        {
            it = m_enemies.erase(it);
            // TODO: decrement health of player
            continue;
        }

        it++;
    }
}

bool Game::input()
{
    switch (getch())
    {
    case 'q':
        return false;
    case 'a':
        m_player.move(Vec2(0, -1));
        break;
    case 'd':
        m_player.move(Vec2(0, 1));
        break;
    case ' ':
        shoot();
        break;
    }

    return true;
}

void Game::shoot()
{
    m_bullet_translations.emplace_back(m_player.translation().y - 1, m_player.translation().x);
}
