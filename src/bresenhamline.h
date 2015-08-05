/**
 *  bresenhamline.h - folly
 *
 *  This module defines ...
 *
 */

#ifndef BRESENHAMLINE_H_
#define BRESENHAMLINE_H_

#include "mapcoordinate.h"

/**
 *  A singly linked list element representing one location in a Bresenham line trace
 */
typedef struct _BresenhamLine BresenhamLine;
struct _BresenhamLine {
    MapCoordinate location;
    BresenhamLine* next;
};

/**
 *  Initializes a line tracing from starting location to stopping location built using Bresenham's Line Alogrithm
 */
//BresenhamLine initBresenhamLine(MapCoordinate startLoc, MapCoordinate stopLoc);

/**
 *  Frees dynamically allocated memory used for BresenhamLine
 */
//void deleteBresenhamLine(BresenhamLine* line);


#endif // BRESENHAMLINE_H_
