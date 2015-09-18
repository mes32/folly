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
typedef struct _DebugStack DebugStack;

DebugStack* DEBUG_STACK;
int DEBUG_SCROLL_UP;
int DEBUG_SCROLL_DOWN;


/**
 * Initialize the stack of debug messages
 */
void initDebugStack();

/**
 * Deletes the stack of debug messages
 */
void deleteDebugStack(DebugStack** stackRef);

/**
 * Creates a new debug message
 */
void debugMessage(const char* message);

/**
 * Display the debugging messages in the ncurses window
 */
void displayDebugStack(const WINDOW* window);

/**
 * Scrolls up the stack of debugging messages (towards older messages)
 */
void debugScrollUp();

/**
 * Scrolls down the stack of debugging messages (towards newer messages)
 */
void debugScrollDown();

#endif // DEBUGFOLLY_H_
