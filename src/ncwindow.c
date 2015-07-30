/**
 *  ncwindow.c - folly
 *
 *  This module defines the main window used for the game's text-based display. This module primarily serves to 
 *  configure folly's usage of the 'ncurses' library.
 *
 */

#include <sys/ioctl.h>
//#include <stdio.h>
#include <ncurses.h>
#include "ncwindow.h"


// The window width in characters
static const int WIDTH = 500;

// The window height in characters
static const int HEIGHT = 500;


/**
 *  Initializes ncurses-based display mode and returns a pointer to the current WINDOW
 */
WINDOW* startNCWindow() {

	initscr();
	noecho();
    curs_set(FALSE);
	cbreak();	// Line buffering disabled. Pass on everything

    struct winsize terminalWindow;
    ioctl(0, TIOCGWINSZ, &terminalWindow);
    int rows = terminalWindow.ws_row;
    int columns = terminalWindow.ws_col;

	WINDOW *window;
	window = newwin(rows, columns, 0, 0);

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
 *  Initializes color pairs for use with the ncurses display window
 */
void initColors() {
	start_color();

	init_pair(WHITE_ON_BLACK, COLOR_WHITE, COLOR_BLACK);  // 1 - white on black
	init_pair(BLUE_ON_BLACK, COLOR_BLUE, COLOR_BLACK);    // 2 - blue on black
	init_pair(RED_ON_BLACK, COLOR_RED, COLOR_BLACK);      // 3 - red on black
	init_pair(BLACK_ON_WHITE, COLOR_BLACK, COLOR_WHITE);  // 4 - black on white
	init_pair(BLUE_ON_WHITE, COLOR_BLUE, COLOR_WHITE);    // 5 - blue on white
}

/**
 *  Prints a character c at location (x, y) using a given ncurses color pair
 */
void printChar(char c, int x, int y, textColorPair color) {

    char buffer[2];
    buffer[0] = c;
    buffer[1] = '\0';

    	attron(COLOR_PAIR(color));
    mvprintw(y, x, buffer);
    attroff(COLOR_PAIR(color));
}

/**
 *  Prints a bold character c at location (x, y) using a given ncurses color pair
 */
void printCharBold(char c, int x, int y, textColorPair color) {
    attron(A_BOLD);
    printChar(c, x, y, color);
    attroff(A_BOLD);
}

/**
 *  Prints a character c at relative location (x, y) where the player's position is centered on the window
 */
void printCharPC(char c, int x, int y, WINDOW* window, int playerX, int playerY, textColorPair color) {

    int maxX;
    int maxY;
    getmaxyx(window, maxY, maxX);

    int centerX = maxX/2;
    int centerY = (maxY-3)/2;

    int deltaX = centerX - playerX;
    int deltaY = centerY - playerY;

    printChar(c, x + deltaX, y + deltaY, color);
}

/**
 *  Prints a bold character c at relative location (x, y) where the player's position is centered on the window
 */
void printCharBoldPC(char c, int x, int y, WINDOW* window, int playerX, int playerY, textColorPair color) {
    attron(A_BOLD);
    printCharPC(c, x, y, window, playerX, playerY, color);
    attroff(A_BOLD);
}

/**
 *  Prints an integer c at location (x, y) using a given ncurses color pair
 */
void printInt(int c, int x, int y, textColorPair color) {
    c %= 10;
    c += 48;
    char castToChar = (char) c;

    printChar(castToChar, x, y, color);
}
