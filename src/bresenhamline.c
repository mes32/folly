/**
 *  bresenhamline.c - folly
 *
 *  This module defines a line created using Bresenham's Line Algorithm represented as a linked list of MapCoordinates
 *
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "debugfolly.h"
#include "bresenhamline.h"

/**
 * Initialize a Bresenham line
 */
BresenhamLine* initBresenhamLine(MapCoordinate startPos, MapCoordinate endPos) {

    BresenhamLine* line = malloc(sizeof(BresenhamLine));
    assert(line != NULL);

    line->head = NULL;
    line->tail = NULL;

    double x_0 = (double)startPos.x;
    double y_0 = (double)startPos.y;
    double x_N = (double)endPos.x;
    double y_N = (double)endPos.y;

    //line->location = initMapCoordinate(startLoc.x, startLoc.y);
    //line->next = NULL;
    //BresenhamLine* current = line;

    double deltaX = x_N - x_0;
    double deltaY = y_N - y_0;
    double error = 0;
    if (deltaX != 0) {
        double deltaError = abs(deltaY / deltaX);
        int y = y_0;
        for (int x=x_0; x <= x_N; x++) {
            MapCoordinate position = initMapCoordinate(x, y);
            enqueueBresenhamLine(line, position);
            error = error + deltaError;
            /*while (error >= 0.5) {
                MapCoordinate position = initMapCoordinate(x, y);
                enqueueBresenhamLine(line, position);
                if (deltaY > 0) {
                    y += 1;
                }
                if (deltaY < 0) {
                    y -= 1;
                }
                error -= 1.0;
            }*/
        }
        for (int x=x_0; x >= x_N; x--) {
            MapCoordinate position = initMapCoordinate(x, y);
            enqueueBresenhamLine(line, position);
            error = error + deltaError;
            /*while (error >= 0.5) {
                MapCoordinate position = initMapCoordinate(x, y);
                enqueueBresenhamLine(line, position);
                if (deltaY > 0) {
                    y += 1;
                }
                if (deltaY < 0) {
                    y -= 1;
                }
                error -= 1.0;
            }*/
        }

    } else {
        if (deltaY > 0) {
            for (int y=y_0; y <= y_N; y++) {
                MapCoordinate position = initMapCoordinate(x_0, y);
                enqueueBresenhamLine(line, position);
            }
        } else {
            for (int y=y_0; y >= y_N; y--) {
                MapCoordinate position = initMapCoordinate(x_0, y);
                enqueueBresenhamLine(line, position);
            }
        }
    }
    return line;
}

/**
 * Enqueues a new position in the Bresenham line
 */
void enqueueBresenhamLine(BresenhamLine* line, MapCoordinate position) {
    BresenhamLineNode* newNode = initBresenhamLineNode(position);
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
MapCoordinate denqueueBresenhamLine(BresenhamLine* line) {
    BresenhamLineNode* oldHead = line->head;
    MapCoordinate position = oldHead->position;
    line->head = line->head->next;
    deleteBresenhamLineNode(&oldHead);
    return position;
}

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
BresenhamLineNode* initBresenhamLineNode(MapCoordinate position) {
    BresenhamLineNode* node = malloc(sizeof(BresenhamLineNode));
    assert(node != NULL);

    node->position = initMapCoordinate(position.x, position.y);
    node->test = 33;
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
