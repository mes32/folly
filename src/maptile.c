/**
 *  maptile.c - folly
 *
 *  This module defines a single tile element in the game map. The main game map is a grid composed of these ASCII-based tiles.
 *
 */

#include "mapcoordinate.h"
#include "maptile.h"


/**
 *  Initializes a map tile
 */
MapTile initMapTile(int x, int y, int isWall) {
    MapTile mapTile;
    mapTile.position = initMapCoordinate(x, y);
    mapTile.explored = 0;
    mapTile.visible = 0;
    mapTile.isWall = isWall;
    return mapTile;
}

/**
 *  Displays the map tile in an ncurses window at the given coordinates
 */
void displayMapTile(WINDOW* window, MapTile* tile, MapCoordinate playerPosition) {

    MapCoordinate tilePosition = tile->position;

    if (tile->explored) {
        if (tile->visible) {
            if (tile->isWall) {
                printCharPC('#', tilePosition, window, playerPosition, WHITE_ON_BLACK);
                return;
            } else {
                printCharPC('.', tilePosition, window, playerPosition, WHITE_ON_BLACK);
                return;
            }
        } else {
            if (tile->isWall) {
                printCharPC('#', tilePosition, window, playerPosition, RED_ON_BLACK);
                return;
            } else {
                printCharPC(' ', tilePosition, window, playerPosition, RED_ON_BLACK);
                return;
            }
        }
    } else {
        printCharPC(' ', tilePosition, window, playerPosition, WHITE_ON_BLACK);
        return;
    }
}

