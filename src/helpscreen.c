/**
 *  helpscreen.c - folly
 *
 *  This module defines the help screen
 *
 */

#include <stdlib.h>
#include <unistd.h>

#include "debugfolly.h"
#include "helpscreen.h"
#include "ncwindow.h"


static const int DISPLAY_DELAY = 30000;

/**
 * Displays the help screen
 */
void displayHelpScreenStart(WINDOW* window) {

    clear();

    int maxY = 24;
    int maxX = 80;
    getmaxyx(window, maxY, maxX);


    for (int y=0; y <= maxY; y++) {
        for (int x=0; x <= maxX; x++) {
            MapCoordinate position = initMapCoordinate(x, y);
            printChar('X', position, BLACK_ON_WHITE);
        }
    }

    refresh();
    usleep(2000000);
}

/**
 * Displays the help screen
 */
void displayHelpScreen(WINDOW* window) {

    clear();

    int maxY = 24;
    int maxX = 80;
    getmaxyx(window, maxY, maxX);


    for (int y=0; y <= maxY; y++) {
        for (int x=0; x <= maxX; x++) {
            MapCoordinate position = initMapCoordinate(x, y);
            printChar('X', position, BLACK_ON_WHITE);
        }
    }

    refresh();
    wgetch(window);
}






