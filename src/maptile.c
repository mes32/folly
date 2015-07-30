/**
 *  maptile.c - folly
 *
 *  This module defines a single tile element in the game map. The main game map is a grid composed of these ASCII-based tiles.
 *
 */

#include "maptile.h"
#include "playercharacter.h"


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
void displayMapTile(WINDOW* window, MapTile* tile, int x, int y, PlayerCharacter* player) {
    if (tile->explored) {
        if (tile->visible) {
            if (tile->isWall) {
                printCharPC('#', x, y, window, player->x, player->y, WHITE_ON_BLACK);
            } else {
                printCharPC('.', x, y, window, player->x, player->y, WHITE_ON_BLACK);
            }
        } else {
            if (tile->isWall) {
                printCharPC('#', x, y, window, player->x, player->y, RED_ON_BLACK);
            } else {
                printCharPC(' ', x, y, window, player->x, player->y, RED_ON_BLACK);
            }
        }
    } else {
        printCharPC(' ', x, y, window, player->x, player->y, WHITE_ON_BLACK);
    }
}

/**
 *  Displays the map tile in an ncurses window at the given coordinates
 */
//static void displayUnexplored(int x, int y) {
//    int k = 0;
//}
