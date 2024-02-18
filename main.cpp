#include <ncurses.h>
#include <time.h>
#include <random>
#include "colors.h"
#include "menu.h"

void quit();

int main()
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

    Menu menu(
        25,
        "StarWars",
        {
            MenuItem("Continue", []() {}),
            MenuItem("New Game", []() {}),
            MenuItem("Quit", quit),
        });
    menu.start();

    endwin();
}

void quit()
{
    endwin();
    exit(0);
}
