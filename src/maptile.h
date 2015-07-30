/**
 *  maptile.h - folly
 *
 *  This module defines a single tile element in the game map. The main game map is a grid composed of these ASCII-based tiles.
 *
 */

#ifndef MAPTILE_H_
#define MAPTILE_H_

#include "ncwindow.h"
#include "playercharacter.h"

/**
 *  A tile in the game map
 */
typedef struct _MapTile {
    //MapTileType* type;
    int explored;
    int visible;

    int isWall; // *** Replace with type eventually
} MapTile;

/**
 *  Initializes a map tile
 */
MapTile initMapTile(int isWall);

/**
 *  Displays the map tile in an ncurses window at the given coordinates
 */
void displayMapTile(WINDOW* window, MapTile* tile, int x, int y, PlayerCharacter* player);


#endif // MAPTILE_H_
