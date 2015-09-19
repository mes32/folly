/**
 *  maptile.h - folly
 *
 *  This module defines a single tile element in the game map. The main game map is a grid composed of these ASCII-based tiles.
 *
 */

#ifndef MAPTILE_H_
#define MAPTILE_H_

#include "mapcoordinate.h"
#include "ncwindow.h"
//#include "enemies.h"

/**
 * A tile in the game map
 */
typedef struct _MapTile {
    MapCoordinate position;
    int explored;
    int visible;
    struct _Enemy* enemy;
    int isWall; // *** Replace with type eventually
} MapTile;

/**
 * Initialize a map tile
 */
MapTile* initMapTile(int x, int y, int isWall);

/**
 * Delete a map tile
 */
void deleteMapTile(MapTile** mapTileRef);

/**
 * Displays the map tile in an ncurses window at the given coordinates
 */
void displayMapTile(const WINDOW* window, const MapTile* tile, MapCoordinate playerPosition);


#endif // MAPTILE_H_
