#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>

#include "ncwindow.h"

static const int WIDTH = 100;
static const int HEIGHT = 100;

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
