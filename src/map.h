/**
 *  map.h - folly
 *
 *  This module defines the two dimensional grid of ASCII tiles used as the main gameplay map.
 *
 */

#ifndef MAP_H_
#define MAP_H_

/**
 *  A gameplay map composed of a two dimensional grid of map tiles
 */
typedef struct _Map {
    char tiles[20][10];
} Map;

/**
 *  Initializes the game map
 */
Map* initMap();

/**
 *  Displays the map in a ncurses window
 */
void displayMap(WINDOW* window, Map* map);

#endif // MAP_H_
