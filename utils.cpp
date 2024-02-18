#include <ncurses.h>
#include <string.h>
#include <algorithm>
#include "vec2.h"

void inputn(const char *prompt, Vec2 translation, int n, char *s)
{
    int prompt_len = strlen(prompt);
    int width = std::max(n, prompt_len) + 4;

    WINDOW *win = newwin(3, width, translation.y, translation.x);
    box(win, 0, 0);
    mvwprintw(win, 0, (width - prompt_len) / 2, "%s", prompt);

    echo();
    curs_set(1);

    mvwgetnstr(win, 1, 2, s, n);

    noecho();
    curs_set(0);

    delwin(win);
}
