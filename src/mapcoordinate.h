/**
 *  mapcoordinate.h - folly
 *
 *  This module defines ...
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
 *  Moves the map coordinates by (deltaX, deltaY)
 */
void movePosition(MapCoordinate* position, int deltaX, int deltaY);


#endif // MAPCOORDINATE_H_
