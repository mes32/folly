/**
 *  map.h - folly
 *
 *  This module defines the two dimensional grid of ASCII tiles used as the main gameplay map.
 *
 */

#ifndef MAP_H_
#define MAP_H_

#include "mapcoordinate.h"
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
Map initMap();

/**
 *  Frees dynamically allocated memory used for map tiles
 */
void deleteMap(Map* map);

/**
 *  Displays the map in an ncurses window
 */
void displayMap(WINDOW* window, Map* map, MapCoordinate playerPosition);

void updateVisibility(Map* map, MapCoordinate playerPosition, int lightRadius);

int isLocationWall(Map* map, MapCoordinate location);

void setVisibility(Map* map, MapCoordinate location, int visibility);

#endif // MAP_H_
