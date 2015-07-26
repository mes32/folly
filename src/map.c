/**
 *  map.c - folly
 *
 *  This module defines the grid of ASCII tiles used as the main gameplay map.
 *
 */

#include <ncurses.h>
#include "map.h"
#include "ncwindow.h"

// 
static const int X_DIM = 20;

// 
static const int Y_DIM = 10;

/**
 *  Initializes the game map
 */
Map* initMap() {
    Map map;
    Map* mapPtr = &map;

    for (int x=0; x < X_DIM; x++) {
        for (int y=0; y < Y_DIM; y++) {
            if (x == 0 || y == 0 || x == X_DIM-1 || y == Y_DIM-1) {
                map.tiles[x][y] = '#';
            } else {
                map.tiles[x][y] = '.';
            }
        }
    }

    return mapPtr;
}

/**
 *  Displays the map in a ncurses window
 */
void displayMap(WINDOW* window, Map* map) {

    char buffer[2];
    buffer[0] = ' ';
    buffer[1] = '\0';

    for (int x=0; x < X_DIM; x++) {
        for (int y=0; y < Y_DIM; y++) {
            //buffer[0] = map->tiles[x][y];
            //printf("(%d, %d) = %c\n", x, y, map->tiles[x][y]);

            buffer[0] = 'x';

    	        attron(COLOR_PAIR(1));
            mvprintw(y, x, buffer);
            attroff(COLOR_PAIR(1));
        }
    }
}

