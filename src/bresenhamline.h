/**
 *  bresenhamline.h - folly
 *
 *  This module defines a line created using Bresenham's Line Algorithm represented as a linked list of MapCoordinates
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
void initBresenhamLine(BresenhamLine** lineRef, MapCoordinate startLoc, MapCoordinate endLoc);

/**
 *  Frees dynamically allocated memory used for BresenhamLine
 */
void deleteBresenhamLine(BresenhamLine** line);


#endif // BRESENHAMLINE_H_
