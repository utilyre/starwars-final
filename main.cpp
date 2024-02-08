#include <iostream>
#include <ncurses.h>

int main() {
    initscr();
    noecho();
    curs_set(0);

    printw("Hello world");
    getch();

    endwin();
}
