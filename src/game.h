/**
 *  game.h - folly
 *
 *  This module defines gameplay in folly at the highest level of abstraction.
 *
 */

#ifndef GAME_H_
#define GAME_H_


/**
 *  Grid coordinates of objects in the game space
 */
typedef struct Coordinates Coordinates;
struct Coordinates {
    int x;
    int y;
};

/**
 *  Configuration of all game objects at one time-step
 */
typedef struct GameState GameState;
struct GameState {
    int moveDir;
    Coordinates playerPosition;
    Coordinates maximumPosition;
};

/**
 *  Initializes the game state and saves the ncurses display window
 */
void initGame(WINDOW* window);

/**
 *  Runs the main game loop (increments game state time-steps)
 */
void runGame();

#endif // GAME_H_
