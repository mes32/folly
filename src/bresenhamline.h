/**
 *  bresenhamline.h - folly
 *
 *  This module defines a line created using Bresenham's Line Algorithm represented as a linked list of MapCoordinates
 *
 */

#ifndef BRESENHAMLINE_H_
#define BRESENHAMLINE_H_

#include "mapcoordinate.h"


// A singly linked list node for a single location along a Bresenham line trace
typedef struct _BresenhamLineNode BresenhamLineNode;
struct _BresenhamLineNode {
    MapCoordinate position;
    int test;
    BresenhamLineNode* next;
};

// A Bresenham line trace
typedef struct _BresenhamLine BresenhamLine;
struct _BresenhamLine {
    BresenhamLineNode* head;
    BresenhamLineNode* tail;
};


/**
 * Initialize a Bresenham line
 */
BresenhamLine* initBresenhamLine(MapCoordinate startLoc, MapCoordinate endLoc);

/**
 * Enqueues a new position in the Bresenham line
 */
void enqueueBresenhamLine(BresenhamLine* line, MapCoordinate position);

/**
 * Denqueues the next position from the Bresenham line
 */
MapCoordinate denqueueBresenhamLine(BresenhamLine* line);

/**
 * Delete a Bresenham line
 */
void deleteBresenhamLine(BresenhamLine** lineRef);

/**
 * Initialize a Bresenham line node 
 */
BresenhamLineNode* initBresenhamLineNode(MapCoordinate position);

/**
 * Delete a Bresenham line node
 */
void deleteBresenhamLineNode(BresenhamLineNode** nodeRef);


#endif // BRESENHAMLINE_H_
