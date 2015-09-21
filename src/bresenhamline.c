/**
 *  bresenhamline.c - folly
 *
 *  This module defines a line created using Bresenham's Line Algorithm represented as a linked list of MapCoordinates
 *
 */

#include <assert.h>
#include <stdlib.h>

#include "debugfolly.h"
#include "bresenhamline.h"

/**
 * Initialize a Bresenham line
 */
BresenhamLine* initBresenhamLine(MapCoordinate startPos, MapCoordinate endPos) {

    BresenhamLine* line = malloc(sizeof(BresenhamLine));
    assert(line != NULL);

    double x_0 = (double)startPos.x;
    double y_0 = (double)startPos.y;
    double x_N = (double)endPos.x;
    double y_N = (double)endPos.y;

    //line->location = initMapCoordinate(startLoc.x, startLoc.y);
    //line->next = NULL;
    //BresenhamLine* current = line;

    double deltaX = x_N - x_0;
    double deltaY = y_N - y_0;
    //double error = 0;
    if (deltaX != 0) {
        //double deltaError = abs(deltaY / deltaX)    // Assume deltax != 0 (line is not vertical),
           // note that this division needs to be done in a way that preserves the fractional part
        //int y := y0
        //for x from x0 to x1
            //plot(x,y)
            //error := error + deltaError
            //while error ≥ 0.5 then
                //plot(x, y)
                //y := y + sign(y1 - y0)
                //error := error - 1.0
    } else {
        if (deltaY > 0) {
            for (int y=y_0; y <= y_N; y++) {
                //MapCoordinate position = initMapCoordinate(x_0, y);
                //enqueueBresenhamLine(line);
            }
        } else {

        }
    }
    return line;
}

/**
 * Enqueues a new position in the Bresenham line
 */
void enqueueBresenhamLine(BresenhamLine* line) {
    BresenhamLineNode* newNode = initBresenhamLineNode(0);
    if (line->tail == NULL) {
        line->head = newNode;
        line->tail = newNode;
    } else {
        line->tail->next = newNode;
        line->tail = newNode;
    }
}

/**
 * Denqueues the next position from the Bresenham line
 */
/*MapCoordinate denqueueBresenhamLine(BresenhamLine* line) {
    BresenhamLineNode* oldHead = line->head;
    MapCoordinate position = oldHead->position; 
    line->head = line->head->next;
    deleteBresenhamLineNode(&oldHead);
    return position;
}*/

/**
 * Delete a Bresenham line
 */
void deleteBresenhamLine(BresenhamLine** lineRef) {
    BresenhamLine* line = *lineRef; 
    while (line->head != NULL) {
        BresenhamLineNode* oldHead = line->head;
        line->head = line->head->next;
        deleteBresenhamLineNode(&oldHead);
    }
   
    free(*lineRef);
    *lineRef = NULL;
}

/**
 * Initialize a Bresenham line node 
 */
BresenhamLineNode* initBresenhamLineNode(int test) {
    BresenhamLineNode* node = malloc(sizeof(BresenhamLineNode));
    assert(node != NULL);

    //node->position = initMapCoordinate(position.x, position.y);
    node->test = test;
    node->next = NULL;

    return node;
}

/**
 * Delete a Bresenham line node
 */
void deleteBresenhamLineNode(BresenhamLineNode** nodeRef) {
    free(*nodeRef);
    *nodeRef = NULL;
}
