#include <algorithm>
#include <ncurses.h>
#include "game.h"
#include "vec2.h"

Game::Game(int size) : m_size(size), m_player(3, Vec2(size - 1, size / 2))
{
    initscr();
    noecho();
    curs_set(0);

    // for test
    m_enemies.emplace_back(1, Vec2(2, 2), Vec2(3, 8));
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
        enemy.render();
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
        enemy.move(Vec2(1, 0));

        if (enemy.bottom() >= m_size - 1)
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
        m_player.move(Vec2(0, -1), Vec2(m_size - 1, 0), Vec2(m_size - 1, m_size - 1));
        break;
    case 'd':
        m_player.move(Vec2(0, 1), Vec2(m_size - 1, 0), Vec2(m_size - 1, m_size - 1));
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
