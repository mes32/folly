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
#include "maptile.h"
#include "map.h"
#include "ncwindow.h"


/**
 *  Initializes the game map
 */
Map initMap(int xDim, int yDim) {
    Map map;
    map.xDim = xDim;
    map.yDim = yDim;

    map.tiles = (MapTile**)malloc(sizeof(MapTile*) * xDim);
    if (! map.tiles) {
        perror("Error allocating memory. See initMap() in map.c");
        abort();
    }

    for (int i=0; i < xDim; i++) {
        map.tiles[i] = (MapTile*)malloc(sizeof(MapTile) * yDim);
        if (! map.tiles[i]) {
            perror("Error allocating memory. See initMap() in map.c");
            abort();
        }
    }

    for (int x=0; x < xDim; x++) {
        for (int y=0; y < yDim; y++) {
            if (x == 0 || y == 0 || x == xDim-1 || y == yDim-1) {
                // Add wall tile
                map.tiles[x][y] = initMapTile(1);
            } else {
                // Add non-wall tile
                map.tiles[x][y] = initMapTile(0);
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
            displayMapTile(&map->tiles[x][y], x, y);
        }
    }
}

