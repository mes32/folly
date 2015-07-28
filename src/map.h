/**
 *  map.h - folly
 *
 *  This module defines the two dimensional grid of ASCII tiles used as the main gameplay map.
 *
 */

#ifndef MAP_H_
#define MAP_H_

#include "maptile.h"

/**
 *  A gameplay map composed of a two dimensional grid of map tiles
 */
typedef struct _Map {
    int xDim;
    int yDim;
    MapTile** tiles;
} Map;

/**
 *  Initializes the game map
 */
Map initMap(int xDim, int yDim);

/**
 *  Frees dynamically allocated memory used for map tiles
 */
void deleteMap(Map* map);

/**
 *  Displays the map in an ncurses window
 */
void displayMap(WINDOW* window, Map* map);

#endif // MAP_H_
