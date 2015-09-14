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

/**
 * Initialize the stack of debug messages
 */
void initDebugStack() {
    DEBUG_STACK = NULL;
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

}
