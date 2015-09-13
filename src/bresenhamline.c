/**
 *  bresenhamline.c - folly
 *
 *  This module defines a line created using Bresenham's Line Algorithm represented as a linked list of MapCoordinates
 *
 */

#include <stdlib.h>
#include "bresenhamline.h"

/**
 *  Initializes a line tracing from starting location to stopping location built using Bresenham's Line Alogrithm
 */
void initBresenhamLine(BresenhamLine** lineRef, MapCoordinate startLoc, MapCoordinate endLoc) {

    BresenhamLine* line = *lineRef;

    double x_0 = (double)startLoc.x;
    double y_0 = (double)startLoc.y;
    //double x_N = (double)endLoc.x;
    double y_N = (double)endLoc.y;

    line = (BresenhamLine*)malloc(sizeof(BresenhamLine));
    line->location = initMapCoordinate(startLoc.x, startLoc.y);
    line->next = NULL;
    BresenhamLine* current = line;

    //double deltaX = x_N - x_0;
    //double deltaY = y_N - y_0;
    //double error = 0;
    //if (deltaX != 0) {
        /*double deltaError = abs(deltaY / deltaX)    // Assume deltax != 0 (line is not vertical),
           // note that this division needs to be done in a way that preserves the fractional part
        int y := y0
        for x from x0 to x1
            plot(x,y)
            error := error + deltaError
            while error ≥ 0.5 then
                plot(x, y)
                y := y + sign(y1 - y0)
                error := error - 1.0*/
    //} else {
        for (int y=y_0; y <= y_N; y++) {
            current->next = (BresenhamLine*)malloc(sizeof(BresenhamLine));
            current = current->next;
            current->location = initMapCoordinate(x_0, y);
            current->next = NULL;
        }
    //}
}

/**
 *  Frees dynamically allocated memory used for BresenhamLine
 */
void deleteBresenhamLine(BresenhamLine** line) {
   // deref head_ref to get the real head
   BresenhamLine* current = *line;
   BresenhamLine* next;
 
   while (current != NULL) 
   {
       next = current->next;
       free(current);
       current = next;
   }
   
   // set contents of line to NULL
   *line = NULL;
}
