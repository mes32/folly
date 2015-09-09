/**
 *  mapcoordinate.c - folly
 *
 *  This module defines a location on the game map based on x-y coordinate space
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
 * Returns the changed map coordinates when moving deltaX, deltaY from current position
 */
MapCoordinate deltaMapCoordiante(MapCoordinate* position, int deltaX, int deltaY) {
    int x = position->x + deltaX;
    int y = position->y + deltaY;
    return initMapCoordinate(x, y);
}

/**
 *  Moves the map coordinates by (deltaX, deltaY)
 */
void movePosition(MapCoordinate* position, int deltaX, int deltaY) {
    position->x += deltaX;
    position->y += deltaY;
}
