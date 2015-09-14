/**
 *  debugfolly.h - folly
 *
 *  This module defines global debugging opertations. This module allows abitrary debug messages to 
 *  be written on top of the ncurses game display.
 *
 */

#ifndef DEBUGFOLLY_H_
#define DEBUGFOLLY_H_

#include "ncwindow.h"


typedef struct _DebugNode DebugNode;

DebugNode* DEBUG_STACK;

/**
 * Initialize the stack of debug messages
 */
void initDebugStack();

/**
 * Creates a new debug message
 */
void debugMessage(const char* message);

/**
 * Display the debugging messages in the ncurses window
 */
void displayDebugStack(WINDOW* window);

#endif // DEBUGFOLLY_H_
