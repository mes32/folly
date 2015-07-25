/**
 *  ncwindow.h - folly
 *
 *  This module defines the main window used for the game's text-based display. This module primarily serves to 
 *  configure folly's usage of the 'ncurses' library.
 *
 */

#ifndef NCWINDOW_H_
#define NCWINDOW_H_


/**
 *  Initializes ncurses-based display mode and returns a pointer to the current WINDOW
 */
WINDOW* startNCWindow();

/**
 *  Closes ncurses-based display mode
 */
void endNCWindow();

#endif // NCWINDOW_H_
