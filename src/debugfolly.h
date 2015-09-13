/**
 *  debugfolly.h - folly
 *
 *  This module defines global debugging opertations. This module allows abitrary debug messages to 
 *  be written on top of the ncurses game display.
 *
 */

#ifndef DEBUGFOLLY_H_
#define DEBUGFOLLY_H_


/**
 * Creates a new debug message
 */
void debugMessage(char* message);


#endif // DEBUGFOLLY_H_
