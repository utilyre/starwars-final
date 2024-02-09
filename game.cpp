#include <algorithm>
#include <ncurses.h>
#include "game.h"
#include "vec2.h"

Game::Game(int size, Vec2 player_translation) : m_size(size), m_player_translation(player_translation)
{
    initscr();
    noecho();
    curs_set(0);
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

    mvprintw(m_player_translation.y, 2 * m_player_translation.x + 1, "#");

    for (Vec2 translation : m_bullet_translations)
    {
        mvprintw(translation.y, 2 * translation.x + 1, "^");
    }
}

void Game::integrate()
{
    for (Vec2 &translation : m_bullet_translations)
    {
        translation.y--;
    }
}

bool Game::input()
{
    switch (getch())
    {
    case 'q':
        return false;
    case 'a':
        move_player(0, -1);
        break;
    case 'd':
        move_player(0, 1);
        break;
    case ' ':
        shoot();
        break;
    }

    return true;
}

void Game::move_player(int dy, int dx)
{
    m_player_translation.y = std::clamp(m_player_translation.y + dy, 0, m_size - 1);
    m_player_translation.x = std::clamp(m_player_translation.x + dx, 0, m_size - 1);
}

void Game::shoot()
{
    m_bullet_translations.emplace_back(m_player_translation.y - 1, m_player_translation.x);
}
