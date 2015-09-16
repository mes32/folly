/**
 *  mapcoordinate.c - folly
 *
 *  This module defines a location on the game map based on x-y coordinate space
 *
 */

#include <math.h>

#include "debugfolly.h"
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
 * Returns the euclidian distance between two map coordinates
 */
double distance(MapCoordinate* position1, MapCoordinate* position2) {
    double x1 = (double)position1->x;
    double y1 = (double)position1->y;
    double x2 = (double)position2->x;
    double y2 = (double)position2->y;

    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

/**
 *  Moves the map coordinates by (deltaX, deltaY)
 */
void movePosition(MapCoordinate* position, int deltaX, int deltaY) {
    position->x += deltaX;
    position->y += deltaY;
}
