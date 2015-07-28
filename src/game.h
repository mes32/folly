/**
 *  game.h - folly
 *
 *  This module defines gameplay in folly at the highest level of abstraction.
 *
 */

#ifndef GAME_H_
#define GAME_H_

#include "ncwindow.h"

/**
 *  Initializes the game state and retains a pointer to the ncurses display window
 */
void initGame(WINDOW* window);

/**
 *  Runs the main game loop (increments game state time-steps)
 */
void runGame();

#endif // GAME_H_
