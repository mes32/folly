/**
 *  game.c - folly
 *
 *  This module defines gameplay in folly at the highest level of abstraction.
 *
 */

#include <unistd.h>
#include "game.h"
#include "map.h"
#include "ncwindow.h"
#include "playercharacter.h"
#include "statusbar.h"
#include "eventwindow.h"


/**
 *  Grid coordinates of objects in the game space
 */
typedef struct _Coordinates {
    int x;
    int y;
} Coordinates;

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
static void initGameState();
static void updateGameState(int input);


/**
 *  Initializes the game state and retains a pointer to the ncurses display window
 */
void initGame(WINDOW* ncursesWindow) {
    window = ncursesWindow;
    initColors();
    initGameState();
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

    displayMap(window, &gameState.map);
    displayPlayerCharacter(&gameState.player);
    displayStatusBar(window, &gameState.player);
    //displayEventWindow(window, &gameState.eventQueue);

    wmove(window, 0, 0);
    usleep(DISPLAY_DELAY);
    refresh();
}

/**
 *  Initializes the game in the starting state
 */
static void initGameState() {

    gameState.map = initMap(20, 10);

    gameState.player = initPlayerCharacter();

    gameState.eventQueue[0] = "You walk up.";
    gameState.eventQueue[1] = "You walk right.";
    gameState.eventQueue[2] = "You walk down.";
}

/**
 *  Increments the game state by one time step based on the player's input 
 */
static void updateGameState(int input) {
    switch(input) {
        case 'k':
        case KEY_UP:
            movePlayerCharacter(&gameState.player, 0, -1);
            break;
        case 'j':
        case KEY_DOWN:
            movePlayerCharacter(&gameState.player, 0, 1);
            break;
        case 'h':
        case KEY_LEFT:
            movePlayerCharacter(&gameState.player, -1, 0);
            break;
        case 'l':
        case KEY_RIGHT:
            movePlayerCharacter(&gameState.player, 1, 0);
            break;
        case 'y':
            movePlayerCharacter(&gameState.player, -1, -1);
            break;
        case 'u':
            movePlayerCharacter(&gameState.player, 1, -1);
            break;
        case 'b':
            movePlayerCharacter(&gameState.player, -1, 1);
            break;
        case 'n':
            movePlayerCharacter(&gameState.player, 1, 1);
            break;
        default:
            break;
    }
}


