/**
 *  mapcoordinate.c - folly
 *
 *  This module defines ...
 *
 */

#include "mapcoordinate.h"


/**
 *  Initializes map coordinates
 */
MapCoordinate initMapCoordinate(int x, int y) {
    MapCoordinate position;
    position.x = x;
    position.y = y;
    return position;
}

/**
 *  Moves the map coordinates by (deltaX, deltaY)
 */
void movePosition(MapCoordinate* position, int deltaX, int deltaY) {
    position->x += deltaX;
    position->y += deltaY;
}
