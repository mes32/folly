/**
 *  ncwindow.h - folly
 *
 *  This module defines the main window used for the game's text-based display. This module primarily serves to 
 *  configure folly's usage of the 'ncurses' library.
 *
 */

#ifndef NCWINDOW_H_
#define NCWINDOW_H_

#include <ncurses.h>

/**
 *  Initializes ncurses-based display mode and returns a pointer to the current WINDOW
 */
WINDOW* startNCWindow();

/**
 *  Closes ncurses-based display mode
 */
void endNCWindow();

/**
 *  Prints a character c at location (x, y) using a given ncurses color pair
 */
void printChar(char c, int x, int y, int colorPair);

/**
 *  Prints a bold character c at location (x, y) using a given ncurses color pair
 */
void printCharBold(char c, int x, int y, int colorPair);

/**
 *  Prints an integer c at location (x, y) using a given ncurses color pair
 */
void printInt(int c, int x, int y, int colorPair);

#endif // NCWINDOW_H_
