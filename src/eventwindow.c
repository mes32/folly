/**
 *  eventwindow.c - folly
 *
 *  This module defines ...
 *
 */

#include "eventwindow.h"
#include "ncwindow.h"


/**
 *  Displays the ...
 */
void displayEventWindow(WINDOW* window) {
    int maxY = 24;
    int maxX = 80;
    getmaxyx(window, maxY, maxX);

    for (int y=maxY-3; y <= maxY; y++) {
        for (int x=0; x <= maxX; x++) {
            printChar(' ', x, y, BLACK_ON_WHITE);
        }
    }
}


