#include <ncurses.h>
#include <string>
#include "vec2.h"

void inputn(const std::string &prompt, Vec2 translation, int n, char *s)
{
    WINDOW *win = newwin(3, n + 4, translation.y, translation.x);
    box(win, 0, 0);
    mvwprintw(win, 0, (n + 4 - prompt.size()) / 2, "%s", prompt.c_str());

    echo();
    curs_set(1);

    mvwgetnstr(win, 1, 2, s, n);

    noecho();
    curs_set(0);

    delwin(win);
}
