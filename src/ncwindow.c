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

/**
 *  Prints a character c at location (x, y) using a given ncurses color pair
 */
void printChar(char c, int x, int y, int colorPair) {

    char buffer[2];
    buffer[0] = c;
    buffer[1] = '\0';

    	attron(COLOR_PAIR(colorPair));
    mvprintw(y, x, buffer);
    attroff(COLOR_PAIR(colorPair));
}

/**
 *  Prints a bold character c at location (x, y) using a given ncurses color pair
 */
void printCharBold(char c, int x, int y, int colorPair) {
    attron(A_BOLD);
    printChar(c, x, y, colorPair);
    attroff(A_BOLD);
}

/**
 *  Prints an integer c at location (x, y) using a given ncurses color pair
 */
void printInt(int c, int x, int y, int colorPair) {
    c %= 10;
    c += 48;
    char castToChar = (char) c;

    printChar(castToChar, x, y, colorPair);
}
