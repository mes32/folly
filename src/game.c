/**
 *  game.c - folly
 *
 *  This module defines gameplay in folly at the highest level of abstraction.
 *
 */

#include <stdlib.h>
#include <unistd.h>

#include "debugfolly.h"
#include "game.h"
#include "helpscreen.h"
#include "map.h"
#include "ncwindow.h"
#include "playercharacter.h"
#include "randfolly.h"
#include "statusbar.h"
#include "storyevent.h"
#include "eventwindow.h"
#include "enemies.h"


/**
 *  Configuration of all game objects at one time-step
 */
typedef struct _GameState {
    Map* map;

    PlayerCharacter* player;

    StoryStack* storyEvents;

    AllEnemies* allEnemies;

} GameState;


// Display delay in microseconds for the ncurses window
static const int DISPLAY_DELAY = 30000;

// Ncurses window used to display the game
static WINDOW* window;

// The current state of all game related objects and data
static GameState gameState;


// Static function prototypes
//static void displayHelpScreen();
static void displayGameScreen();
static void initGameState(unsigned int randomSeed);
static void updateGameState(int input);


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

    //displayHelpScreen(window);

    int c = 0;
	while(1) {

        while (c == DEBUG_SCROLL_UP || c == DEBUG_SCROLL_DOWN) {
            if (c == DEBUG_SCROLL_UP) {
                debugScrollUp();
                displayGameScreen();
            } else {
                debugScrollDown();
                displayGameScreen();
            }
            c = wgetch(window);
        }

        /*if (c == '?' || c == 27) {
            displayHelpScreen(window);
        }*/

        updateGameState(c);
        displayGameScreen();
        c = wgetch(window);
	}
}

/**
 *  Displays the game instructions (help screen)
 */
/*static void displayHelpScreen() {
    clear();
	mvprintw(0, 0, "Use arrow keys to move around");
    usleep(DISPLAY_DELAY);
	refresh();

    int c = wgetch(window);
}*/

/**
 *  Displays the current game state (main game screen)
 */
static void displayGameScreen() {
    clear();

    displayMap(window, gameState.map, gameState.player->position);
    displayAllEnemies(window, gameState.player, gameState.allEnemies, gameState.map);
    displayPlayerCharacter(window, gameState.player);
    displayStatusBar(window, gameState.player);
    displayEventWindow(window, gameState.storyEvents);

    wmove(window, 0, 0);
    usleep(DISPLAY_DELAY);
    refresh();
}

/**
 *  Initializes the game in the starting state
 */
static void initGameState(unsigned int randomSeed) {

    initRandomSeed(randomSeed);
    gameState.map = initMap();
    gameState.player = initPlayerCharacter();
    gameState.allEnemies = initAllEnemies(gameState.map, gameState.player->position);
    gameState.storyEvents = initStoryStack(gameState.allEnemies->levelBoss->name);
}

/**
 *  Increments the game state by one time step based on the player's input 
 */
static void updateGameState(int input) {

    int deltaX = 0;
    int deltaY = 0;

    StoryEvent* movementEvent;

    switch(input) {
        case 'k':
        case KEY_UP:
            deltaY = -1;
            movementEvent = initStoryEvent("You walk north.");
            break;
        case 'j':
        case KEY_DOWN:
            deltaY = 1;
            movementEvent = initStoryEvent("You walk south.");
            break;
        case 'h':
        case KEY_LEFT:
            deltaX = -1;
            movementEvent = initStoryEvent("You walk west.");
            break;
        case 'l':
        case KEY_RIGHT:
            deltaX = 1;
            movementEvent = initStoryEvent("You walk east.");
            break;
        case 'y':
            deltaX = -1;
            deltaY = -1;
            movementEvent = initStoryEvent("You walk northwest.");
            break;
        case 'u':
            deltaX = 1;
            deltaY = -1;
            movementEvent = initStoryEvent("You walk northeast.");
            break;
        case 'b':
            deltaX = -1;
            deltaY = 1;
            movementEvent = initStoryEvent("You walk southwest.");
            break;
        case 'n':
            deltaX = 1;
            deltaY = 1;
            movementEvent = initStoryEvent("You walk southeast.");
            break;
        default:
            //return;
            break;
    }

    MapCoordinate newPosition = deltaMapCoordiante(&gameState.player->position, deltaX, deltaY);

    if (isTraversable(gameState.map, newPosition)) {
        movePlayerCharacter(gameState.player, deltaX, deltaY);
    } else {
        movementEvent = initStoryEvent("You seem to have hit a wall.");
    }

    //pushStoryStack(gameState.storyEvents, movementEvent);

    updateVisibility(gameState.map, gameState.player->position, gameState.player->lightRadius);
}


