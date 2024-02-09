#include <iostream>
#include <ncurses.h>
#include <algorithm>

const int SIZE = 20;

struct Vec2
{
    int y, x;

    Vec2(int y, int x) : y(y), x(x) {}
};

class Game
{
public:
    Game() : m_player_translation(Vec2(SIZE - 1, SIZE / 2)) {}

    void render() const
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                mvprintw(i, 2 * j, " ");
                if (m_player_translation.y == i && m_player_translation.x == j)
                {
                    printw("#");
                }
                else
                {
                    printw("-");
                }
            }
        }
    }

    void move_player(int dy, int dx)
    {
        m_player_translation.y = std::clamp(m_player_translation.y + dy, 0, SIZE - 1);
        m_player_translation.x = std::clamp(m_player_translation.x + dx, 0, SIZE - 1);
    }

private:
    Vec2 m_player_translation;
};

int main()
{
    Game game;

    initscr();
    noecho();
    curs_set(0);

    // collision_map
    // enemies
    // shots
    // player_x

    while (true)
    {
        game.render();

        switch (getch())
        {
        case 'q':
            endwin();
            exit(0);
        case 'a':
            game.move_player(0, -1);
            break;
        case 'd':
            game.move_player(0, 1);
            break;
        }
    }

    endwin();
    return 0;
}
