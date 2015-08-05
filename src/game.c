/**
 *  game.c - folly
 *
 *  This module defines gameplay in folly at the highest level of abstraction.
 *
 */

#include <stdlib.h>
#include <unistd.h>
#include "game.h"
#include "map.h"
#include "ncwindow.h"
#include "playercharacter.h"
#include "randfolly.h"
#include "statusbar.h"
#include "eventwindow.h"


/**
 *  Configuration of all game objects at one time-step
 */
typedef struct _GameState {
    Map map;

    PlayerCharacter player;

    const char *eventQueue[3];

} GameState;


// Display delay in microseconds for the ncurses window
static const int DISPLAY_DELAY = 30000;

// Ncurses window used to display the game
static WINDOW* window;

// The current state of all game related objects and data
static GameState gameState;


// Static function prototypes
static void displayHelpScreen();
static void displayGameScreen();
static void initGameState(unsigned int randomSeed);
static void updateGameState(int input);
static int isWall(Map* map, MapCoordinate position, int deltaX, int deltaY);


/**
 *  Initializes the game state and retains a pointer to the ncurses display window
 */
void initGame(WINDOW* ncursesWindow, unsigned int randomSeed) {
    window = ncursesWindow;
    initColors();
    initGameState(randomSeed);
}

/**
 *  Runs the main game loop (increments game state time-steps)
 */
void runGame() {

    displayHelpScreen();

    int c;
	while(1) {
        c = wgetch(window);
        updateGameState(c);
        displayGameScreen();
	}
}

/**
 *  Displays the game instructions (help screen)
 */
static void displayHelpScreen() {
    clear();
	mvprintw(0, 0, "Use arrow keys to move around");
	refresh();
}

/**
 *  Displays the current game state (main game screen)
 */
static void displayGameScreen() {
    clear();

    displayMap(window, &gameState.map, gameState.player.position);
    displayPlayerCharacter(window, &gameState.player);
    displayStatusBar(window, &gameState.player);

    //char* events[3] = gameState.eventQueue;

    displayEventWindow(window);

    //wmove(window, 0, 0);
    usleep(DISPLAY_DELAY);
    //wrefresh(window);
    refresh();
}

/**
 *  Initializes the game in the starting state
 */
static void initGameState(unsigned int randomSeed) {

    initRandomSeed(randomSeed);

    gameState.map = initMap();

    gameState.player = initPlayerCharacter();

    gameState.eventQueue[0] = "You walk up.";
    gameState.eventQueue[1] = "You walk right.";
    gameState.eventQueue[2] = "You walk down.";
}

/**
 *  Increments the game state by one time step based on the player's input 
 */
static void updateGameState(int input) {

    int deltaX = 0;
    int deltaY = 0;

    switch(input) {
        case 'k':
        case KEY_UP:
            deltaY = -1;
            break;
        case 'j':
        case KEY_DOWN:
            deltaY = 1;
            break;
        case 'h':
        case KEY_LEFT:
            deltaX = -1;
            break;
        case 'l':
        case KEY_RIGHT:
            deltaX = 1;
            break;
        case 'y':
            deltaX = -1;
            deltaY = -1;
            break;
        case 'u':
            deltaX = 1;
            deltaY = -1;
            break;
        case 'b':
            deltaX = -1;
            deltaY = 1;
            break;
        case 'n':
            deltaX = 1;
            deltaY = 1;
            break;
        default:
            break;
    }

    if (! isWall(&gameState.map, gameState.player.position, deltaX, deltaY)) {
        movePlayerCharacter(&gameState.player, deltaX, deltaY);
    }

    updateVisibility(&gameState.map, gameState.player.position, gameState.player.lightRadius);
}

static int isWall(Map* map, MapCoordinate position, int deltaX, int deltaY) {
    return map->tiles[position.y+deltaY][position.x+deltaX].isWall;
}


