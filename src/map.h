/**
 *  map.h - folly
 *
 *  This module defines the two dimensional grid of ASCII tiles used as the main gameplay map.
 *
 */

#ifndef MAP_H_
#define MAP_H_

#include <stdlib.h>

#include "mapcoordinate.h"
#include "maptile.h"


/**
 * A gameplay map composed of a two dimensional grid of map tiles
 */
typedef struct _Map {
    int xDim;
    int yDim;
    MapTile** tiles;
} Map;

/**
 * Initializes the game map
 */
Map* initMap();

/**
 *  Frees dynamically allocated memory used for map tiles
 */
void deleteMap(Map** mapRef);

/**
 * Displays the map in an ncurses window
 */
void displayMap(const WINDOW* window, const Map* map, MapCoordinate playerPosition);

/**
 * Updates the visibility status of map tiles based on the player's position and the radius of illumination around that position
 */
void updateVisibility(Map* map, MapCoordinate playerPosition, int lightRadius);

/**
 * Returns 1 if a given location on the map can be traversed by the player (i.e. no obstacles like walls or enemies). Returns 0 otherwise.
 */
int isTraversable(const Map* map, MapCoordinate location);

/**
 * Returns 1 if a given location on the map is a wall
 */
int isWall(const Map* map, MapCoordinate location);

/**
 * Sets the enemy at a given location
 */
void setEnemy(Map* map, struct _Enemy* enemy, MapCoordinate location);

/**
 * Sets the visibility status of the maptile at a given location.
 */
void setVisibility(Map* map, MapCoordinate location, int visibility);

/**
 * Returns one if the position on the map is visible to the player
 */
int isVisible(const Map* map, MapCoordinate position);

#endif // MAP_H_
