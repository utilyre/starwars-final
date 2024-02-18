#include <ncurses.h>
#include <time.h>
#include <random>
#include "colors.h"
#include "menu.h"
#include "game.h"
#include "utils.h"
#include "rect.h"
#include <string.h>

void init();
void open_menu();

void action_continue(Menu &menu);
void action_new(Menu &menu);
void action_quit(Menu &menu);

int main()
{
    init();
    open_menu();
    endwin();
}

void init()
{
    srand(time(0));

    initscr();
    start_color();
    noecho();
    curs_set(0);

    init_pair(CP_PLAYER, COLOR_BLUE, COLOR_BLACK);
    init_pair(CP_BULLET, COLOR_YELLOW, COLOR_BLACK);
    init_pair(CP_ENEMY, COLOR_RED, COLOR_BLACK);
    init_pair(CP_SELECTED, COLOR_BLACK, COLOR_WHITE);
}

void open_menu()
{
    Menu menu(
        25,
        "StarWars",
        {
            MenuItem("Continue", action_continue),
            MenuItem("New Game", action_new),
            MenuItem("Quit", action_quit),
        });

    menu.start();
}

void action_continue(Menu &menu)
{
    menu.stop();

    Game game;
    game.start();
}

void action_new(Menu &menu)
{
    int size;
    do
    {
        char size_str[3];
        ninput(" Size: ", Rect(3, 48, (LINES - 3) / 2, (COLS - 48) / 2), 2, size_str);

        size = std::atoi(size_str);
    } while (size < 15);

    char max_score_str[5];
    ninput(" Max Score: ", Rect(3, 48, (LINES - 3) / 2, (COLS - 48) / 2), 4, max_score_str);
    int max_score = std::atoi(max_score_str);

    menu.stop();
    Game game(size);
    game.start();
}

void action_quit(Menu &menu)
{
    endwin();
    exit(0);
}
