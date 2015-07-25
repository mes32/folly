#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>

#include "ncwindow.h"

WINDOW* startNCWindow() {

	initscr();
	noecho();
    curs_set(FALSE);
	cbreak();	// Line buffering disabled. Pass on everything
		
	WINDOW *window;
	window = newwin(HEIGHT, WIDTH, HEIGHT, WIDTH);
	keypad(window, TRUE);
	clear();

    return window;
}

void endNCWindow() {
	clrtoeol();
	refresh();
	endwin();
}
