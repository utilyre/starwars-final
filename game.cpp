#include <algorithm>
#include <ncurses.h>
#include <random>
#include <time.h>
#include <fstream>
#include "game.h"
#include "vec2.h"
#include "bullet.h"
#include "colors.h"
#include "menu.h"

Game::Game() : m_stopped(false)
{
    load();

    m_wstatus = newwin(3, 2 * m_size + 3, (LINES - m_size - 8) / 2, (COLS - 2 * m_size - 3) / 2);
    m_wgame = newwin(m_size + 2, 2 * m_size + 3, (LINES - m_size - 2) / 2, (COLS - 2 * m_size - 3) / 2);
}

Game::Game(int size) : m_size(size), m_player(3, Vec2(size - 1, size / 2)), m_stopped(false)
{
    m_wstatus = newwin(3, 2 * m_size + 3, (LINES - m_size - 8) / 2, (COLS - 2 * m_size - 3) / 2);
    m_wgame = newwin(m_size + 2, 2 * m_size + 3, (LINES - m_size - 2) / 2, (COLS - 2 * m_size - 3) / 2);
}

Game::~Game()
{
    delwin(m_wgame);
    delwin(m_wstatus);
}

void Game::start()
{
    if (m_enemies.size() == 0)
    {
        spawn_enemy_randomly();
    }

    while (true)
    {

        render();
        integrate();
        save();

        if (m_stopped || !input())
        {
            return;
        }
    }
}

void Game::stop()
{
    m_stopped = true;

    wclear(m_wstatus);
    wrefresh(m_wstatus);
    wclear(m_wgame);
    wrefresh(m_wgame);
}

void Game::render() const
{
    wclear(m_wstatus);
    box(m_wstatus, 0, 0);
    wclear(m_wgame);
    box(m_wgame, 0, 0);

    if (!m_player.is_dead())
    {
        wattron(m_wgame, COLOR_PAIR(CP_PLAYER));
        m_player.render(m_wstatus, m_wgame);
        wattroff(m_wgame, COLOR_PAIR(CP_PLAYER));
    }

    wattron(m_wgame, COLOR_PAIR(CP_BULLET));
    for (Bullet bullet : m_bullets)
    {
        bullet.render(m_wgame);
    }
    wattroff(m_wgame, COLOR_PAIR(CP_BULLET));

    wattron(m_wgame, COLOR_PAIR(CP_ENEMY));
    for (Enemy enemy : m_enemies)
    {
        enemy.render(m_wgame);
    }
    wattroff(m_wgame, COLOR_PAIR(CP_ENEMY));

    wrefresh(m_wstatus);
    wrefresh(m_wgame);
}

void Game::integrate()
{
    check_gameover();
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

        if (enemy.collides_with(Rect(1, m_size, m_player.translation().y, 0)))
        {
            it = m_enemies.erase(it);
            spawn_enemy_randomly();

            m_player.take_damage(1);
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

            if (enemy.collides_with(Rect(Vec2(2, 1), bullet.translation())))
            {
                should_erase_bullet = true;
                enemy.take_damage(1);
                if (enemy.is_dead())
                {
                    m_player.take_score(enemy.points());
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

void Game::save() const
{
    std::ofstream f("state.dat", std::ios::binary);

    f.write(reinterpret_cast<const char *>(&m_size), sizeof(m_size));

    m_player.save_to(f);

    int bullets_len = m_bullets.size();
    f.write(reinterpret_cast<char *>(&bullets_len), sizeof(bullets_len));
    for (const Bullet &bullet : m_bullets)
    {
        bullet.save_to(f);
    }

    int enemies_len = m_enemies.size();
    f.write(reinterpret_cast<char *>(&enemies_len), sizeof(enemies_len));
    for (const Enemy &enemy : m_enemies)
    {
        enemy.save_to(f);
    }
}

void Game::load()
{
    std::ifstream f("state.dat", std::ios::binary);
    if (!f.is_open())
    {
        return;
    }

    f.read(reinterpret_cast<char *>(&m_size), sizeof(m_size));

    m_player.load_from(f);

    int bullets_len;
    f.read(reinterpret_cast<char *>(&bullets_len), sizeof(bullets_len));
    for (int i = 0; i < bullets_len; i++)
    {
        Bullet bullet;
        bullet.load_from(f);
        m_bullets.push_back(bullet);
    }

    int enemies_len;
    f.read(reinterpret_cast<char *>(&enemies_len), sizeof(bullets_len));
    for (int i = 0; i < enemies_len; i++)
    {
        Enemy enemy;
        enemy.load_from(f);
        m_enemies.push_back(enemy);
    }
}

void Game::check_gameover()
{
    if (m_player.is_dead())
    {
        Menu menu(
            25,
            "Game Over!",
            {
                MenuItem("Try Again", [&](Menu &menu)
                         {
                    menu.stop();

                    m_player = Player(3, Vec2(m_size - 1, m_size / 2));
                    m_bullets.clear();
                    m_enemies.clear();

                    spawn_enemy_randomly();
                    render(); }),
                MenuItem("Quit", [&](Menu &menu)
                         {
                    menu.stop();
                    stop(); }),
            });

        menu.start();
    }
}
