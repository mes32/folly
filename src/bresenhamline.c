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


static double absoluteValue(double input);
static int signFunction(double input);


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

    double deltaX = x_N - x_0;
    double deltaY = y_N - y_0;

    double error = 0.0;
    MapCoordinate position;
    if (deltaX != 0) {
        double deltaError = absoluteValue(deltaY / deltaX);
        int signDeltaY = signFunction(deltaY);

        int y = y_0;
        for (int x=x_0; x <= x_N; x++) {
            position = initMapCoordinate(x, y);
            enqueueBresenhamLine(line, position);

            error += deltaError;
            while (error >= 0.5 && x != x_N && y != y_N) {
                position = initMapCoordinate(x, y);
                enqueueBresenhamLine(line, position);

                y += signDeltaY;
                error -= 1.0;
            }
        }
        for (int x=x_0; x >= x_N; x--) {
            position = initMapCoordinate(x, y);
            enqueueBresenhamLine(line, position);

            error += deltaError;
            while (error >= 0.5 && x != x_N && y != y_N) {
                position = initMapCoordinate(x, y);
                enqueueBresenhamLine(line, position);

                y += signDeltaY;
                error -= 1.0;
            }
        }

    } else {
        if (deltaY > 0) {
            for (int y=y_0; y <= y_N; y++) {
                position = initMapCoordinate(x_0, y);
                enqueueBresenhamLine(line, position);
            }
        } else {
            for (int y=y_0; y >= y_N; y--) {
                position = initMapCoordinate(x_0, y);
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

/**
 * Returns the absolute value of the input retaining double precision
 */
static double absoluteValue(double input) {
        if (input < 0.0) {
            return -1.0 * input;
        } else {
            return input;
        }
}

/**
 * Returns 1 for positive input, -1 for negative, and 0 for input == 0.0
 */
static int signFunction(double input) {
    if (input > 0.0) {
        return 1;
    } else if (input < 0.0) {
        return -1;
    } else {
        return 0;
    }
}
