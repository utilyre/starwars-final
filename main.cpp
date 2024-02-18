#include <ncurses.h>
#include <time.h>
#include <random>
#include "colors.h"
#include "menu.h"
#include "game.h"
#include "utils.h"

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

    Game game(20);
    game.start();
}

void action_new(Menu &menu)
{
    menu.stop();

    char size_str[8];
    inputn("Size:", Vec2((LINES - 3) / 2, (COLS - 8) / 2), 8, size_str);

    char max_score_str[16];
    inputn("Max Score:", Vec2((LINES - 3) / 2, (COLS - 16) / 2), 16, max_score_str);

    Game game(std::atoi(size_str));
    game.start();
}

void action_quit(Menu &menu)
{
    endwin();
    exit(0);
}
