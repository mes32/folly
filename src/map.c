/**
 *  map.c - folly
 *
 *  This module defines the grid of ASCII tiles used as the main gameplay map.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "map.h"
#include "ncwindow.h"


/**
 *  Initializes the game map
 */
Map initMap(int xDim, int yDim) {
    Map map;
    map.xDim = xDim;
    map.yDim = yDim;

    map.tiles = (char**)malloc(sizeof(char*) * xDim);
    if (! map.tiles) {
        perror("Error allocating memory. See initMap() in map.c");
        abort();
    }

    for (int i=0; i < xDim; i++) {
        map.tiles[i] = (char*)malloc(sizeof(char) * yDim);
        if (! map.tiles[i]) {
            perror("Error allocating memory. See initMap() in map.c");
            abort();
        }
    }

    for (int x=0; x < xDim; x++) {
        for (int y=0; y < yDim; y++) {
            if (x == 0 || y == 0 || x == xDim-1 || y == yDim-1) {
                map.tiles[x][y] = '#';
            } else {
                map.tiles[x][y] = '.';
            }
        }
    }

    return map;
}

/**
 *  Frees dynamically allocated memory used for map tiles
 */
void deleteMap(Map* map) {
    for (int x = map->xDim - 1; x >= 0; x--) {
        free(map->tiles[x]);
    }
    free(map->tiles);
}

/**
 *  Displays the map in an ncurses window
 */
void displayMap(WINDOW* window, Map* map) {
    for (int x=0; x < map->xDim; x++) {
        for (int y=0; y < map->yDim; y++) {
            int c = map->tiles[x][y];
            printChar(c, x, y, 1);
        }
    }
}

