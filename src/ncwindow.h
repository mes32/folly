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

typedef enum {
   WHITE_ON_BLACK = 1,
   BLUE_ON_BLACK = 2,
   RED_ON_BLACK = 3
} textColorPair;

/**
 *  Initializes ncurses-based display mode and returns a pointer to the current WINDOW
 */
WINDOW* startNCWindow();

/**
 *  Closes ncurses-based display mode
 */
void endNCWindow();

/**
 *  Initializes color pairs for use with the ncurses display window
 */
void initColors();

/**
 *  Prints a character c at location (x, y) using a given ncurses color pair
 */
void printChar(char c, int x, int y, textColorPair color);

/**
 *  Prints a bold character c at location (x, y) using a given ncurses color pair
 */
void printCharBold(char c, int x, int y, textColorPair color);

/**
 *  Prints an integer c at location (x, y) using a given ncurses color pair
 */
void printInt(int c, int x, int y, textColorPair color);

#endif // NCWINDOW_H_
