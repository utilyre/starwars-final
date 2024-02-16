#include <ncurses.h>
#include <time.h>
#include <random>
#include "startup-menu.h"

int main()
{
    srand(time(0));

    initscr();
    start_color();
    noecho();
    curs_set(0);

    StartupMenu menu;
    menu.start();

    endwin();
}
