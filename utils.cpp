#include <ncurses.h>
#include <string.h>
#include <algorithm>
#include "rect.h"

void ninput(const char *prompt, Rect r, int n, char *s)
{
    WINDOW *win = newwin(r.size.y, r.size.x, r.translation.y, r.translation.x);
    box(win, 0, 0);
    mvwprintw(win, 0, (r.size.x - strlen(prompt)) / 2, "%s", prompt);

    echo();
    curs_set(1);

    mvwgetnstr(win, r.size.y / 2, 2, s, n);

    noecho();
    curs_set(0);

    wclear(win);
    wrefresh(win);
    delwin(win);
}
