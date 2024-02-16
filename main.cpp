#include <ncurses.h>
#include <time.h>
#include <random>
#include "menu.h"

int main()
{
    srand(time(0));

    initscr();
    start_color();
    noecho();
    curs_set(0);

    Menu menu(
        20,
        {
            MenuItem("Continue", []() {}),
            MenuItem("New Game", []() {}),
            MenuItem("Quit", []()
                     {
                endwin();
                exit(0); }),
        });
    menu.start();

    endwin();
}
