#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>

#include "ncwindow.h"

WINDOW* startNCWindow() {

	initscr();
	noecho();
    curs_set(FALSE);
	cbreak();	// Line buffering disabled. Pass on everything
		
	WINDOW *menu_win;
	menu_win = newwin(HEIGHT, WIDTH, HEIGHT, WIDTH);
	keypad(menu_win, TRUE);
	clear();

    return menu_win;
}

void endNCWindow() {
	clrtoeol();
	refresh();
	endwin();
}
