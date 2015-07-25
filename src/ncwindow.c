/**
 *  ncwindow.c - folly
 *
 *  This module defines the main window used for the game's text-based display. This module primarily serves to 
 *  configure folly's usage of the 'ncurses' library.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>


// The window width in characters
static const int WIDTH = 100;

// The window height in characters
static const int HEIGHT = 100;


/**
 *  Initializes ncurses-based display mode and returns a pointer to the current WINDOW
 */
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

/**
 *  Closes ncurses-based display mode
 */
void endNCWindow() {
	clrtoeol();
	refresh();
	endwin();
}
