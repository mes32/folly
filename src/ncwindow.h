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
#include "mapcoordinate.h"

typedef enum {
    WHITE_ON_BLACK = 1,
    BLUE_ON_BLACK = 2,
    RED_ON_BLACK = 3,
    BLACK_ON_WHITE = 4,
    BLUE_ON_WHITE = 5,
    RED_ON_WHITE = 6,
    GREEN_ON_BLACK = 7
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
void printChar(char c, MapCoordinate position, textColorPair color);

/**
 *  Prints a bold character c at location (x, y) using a given ncurses color pair
 */
void printCharBold(char c, MapCoordinate position, textColorPair color);

/**
 *  Prints a character c at relative location (x, y) where the player's position is centered on the window
 */
void printCharPC(char c, MapCoordinate position, WINDOW* window, MapCoordinate playerPosition, textColorPair color);

/**
 *  Prints a bold character c at relative location (x, y) where the player's position is centered on the window
 */
void printCharBoldPC(char c, MapCoordinate position, WINDOW* window, MapCoordinate playerPosition, textColorPair color);

/**
 *  Prints an integer c at location (x, y) using a given ncurses color pair
 */
void printInt(int c, MapCoordinate position, textColorPair color);

#endif // NCWINDOW_H_
