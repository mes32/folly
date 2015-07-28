/**
 *  maptile.c - folly
 *
 *  This module defines a single tile element in the game map. The main game map is a grid composed of these ASCII-based tiles.
 *
 */

#include "maptile.h"


/**
 *  Initializes a map tile
 */
MapTile initMapTile(int isWall) {
    MapTile mapTile;
    mapTile.explored = 0;
    mapTile.visible = 0;
    mapTile.isWall = isWall;
    return mapTile;
}

/**
 *  Displays the map tile in an ncurses window at the given coordinates
 */
void displayMapTile(MapTile* tile, int x, int y) {
    if (tile->isWall) {
        printChar('#', x, y, 1);
    } else {
        printChar('.', x, y, 1);
    }
}

/**
 *  Displays the map tile in an ncurses window at the given coordinates
 */
//static void displayUnexplored(int x, int y) {
//    int k = 0;
//}
