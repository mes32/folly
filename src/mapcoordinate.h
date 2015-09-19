/**
 *  mapcoordinate.h - folly
 *
 *  This module defines a location on the game map based on x-y coordinate space
 *
 */

#ifndef MAPCOORDINATE_H_
#define MAPCOORDINATE_H_

/**
 *  A tile in the game map
 */
typedef struct _MapCoordinate {
    int x;
    int y;
} MapCoordinate;

/**
 *  Initializes map coordinates
 */
MapCoordinate initMapCoordinate(int x, int y);

/**
 * Returns the changed map coordinates when moving deltaX, deltaY from current position
 */
MapCoordinate deltaMapCoordiante(const MapCoordinate* position, int deltaX, int deltaY);

/**
 * Returns the euclidian distance between two map coordinates
 */
double distance(const MapCoordinate* position1, const MapCoordinate* position2);

/**
 *  Moves the map coordinates by (deltaX, deltaY)
 */
void movePosition(MapCoordinate* position, int deltaX, int deltaY);


#endif // MAPCOORDINATE_H_
