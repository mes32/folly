/**
 *  debugfolly.c - folly
 *
 *  This module defines global debugging opertations. This module allows abitrary debug messages to 
 *  be written on top of the ncurses game display.
 *
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "debugfolly.h"
#include "ncwindow.h"


struct _DebugNode {
    char* message;
    DebugNode* next;
    DebugNode* previous;
};

static void printDebug(const DebugNode* node, int y);

/**
 * Initialize the stack of debug messages
 */
void initDebugStack() {
    DEBUG_STACK = NULL;
    DEBUG_SCROLL_UP = (int)'z';
    DEBUG_SCROLL_DOWN = (int)'x';
}

/**
 * Creates a new debug message
 */
void debugMessage(const char* message) {
    size_t len = strlen(message);

    DebugNode* node = malloc(sizeof(DebugNode));
    assert(node != NULL);
    node->message = malloc(len + 1);
    assert(node->message != NULL);

    strcpy(node->message, message);
    node->next = NULL;
    node->previous = NULL;

    if (DEBUG_STACK == NULL) {
        DEBUG_STACK = node;
    } else {
        DEBUG_STACK->next = node;
        node->previous = DEBUG_STACK;
        DEBUG_STACK = node;
    }
}

/**
 * Display the debugging messages in the ncurses window
 */
void displayDebugStack(WINDOW* window) {
    int maxY = 24;
    int maxX = 80;
    getmaxyx(window, maxY, maxX);

    for (int y=1; y <= 3; y++) {
        for (int x=0; x <= maxX; x++) {
            MapCoordinate position = initMapCoordinate(x, y);
            printChar(' ', position, BLACK_ON_WHITE);
        }
    }

    // Print three most recent debug messages
    DebugNode* current = DEBUG_STACK;
    if (current != NULL) {
        printDebug(current, 3);
        current = current->previous;
        if (current != NULL) {
            printDebug(current, 2);
            current = current->previous;
            if (current != NULL) {
                printDebug(current, 1);
            }
        }
    }
}

/**
 * Prints one debug message at the specified vertical possition on the ncurses window. This will 
 * usually be near the top.
 */
static void printDebug(const DebugNode* node, int y) {
    char* message = node->message;

    int x = 0;
    char character = message[x];
    MapCoordinate position = initMapCoordinate(x, y);

    while (character != '\0') {
        printChar(character, position, BLACK_ON_WHITE);
        x++;
        character = message[x];
        position = initMapCoordinate(x, y);
    }
}
