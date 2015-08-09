/**
 *  eventwindow.c - folly
 *
 *  This module defines the game event window that displays story events and narration as the player interacts with the game
 *
 */

#include "eventwindow.h"
#include "mapcoordinate.h"
#include "ncwindow.h"


/**
 * Displays the game story events (i.e. event feed) in a section near the bottom of the game window
 */
void displayEventWindow(WINDOW* window) {
    int maxY = 24;
    int maxX = 80;
    getmaxyx(window, maxY, maxX);

    for (int y=maxY-3; y <= maxY; y++) {
        for (int x=0; x <= maxX; x++) {
            MapCoordinate position = initMapCoordinate(x, y);
            printChar(' ', position, BLACK_ON_WHITE);
        }
    }
}


