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

    //displayHelpScreen();

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

    displayMap(window, gameState.map, gameState.player->position);
    displayAllEnemies(window, gameState.player, gameState.allEnemies, gameState.map);
    displayPlayerCharacter(window, gameState.player);
    displayStatusBar(window, gameState.player);
    displayEventWindow(window, gameState.storyEvents);

    wmove(window, 0, 0);

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
    gameState.allEnemies = initAllEnemies(gameState.map);
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
            initStoryEvent(&movementEvent, "You walk north.");
            break;
        case 'j':
        case KEY_DOWN:
            deltaY = 1;
            initStoryEvent(&movementEvent, "You walk south.");
            break;
        case 'h':
        case KEY_LEFT:
            deltaX = -1;
            initStoryEvent(&movementEvent, "You walk west.");
            break;
        case 'l':
        case KEY_RIGHT:
            deltaX = 1;
            initStoryEvent(&movementEvent, "You walk east.");
            break;
        case 'y':
            deltaX = -1;
            deltaY = -1;
            initStoryEvent(&movementEvent, "You walk northwest.");
            break;
        case 'u':
            deltaX = 1;
            deltaY = -1;
            initStoryEvent(&movementEvent, "You walk northeast.");
            break;
        case 'b':
            deltaX = -1;
            deltaY = 1;
            initStoryEvent(&movementEvent, "You walk southwest.");
            break;
        case 'n':
            deltaX = 1;
            deltaY = 1;
            initStoryEvent(&movementEvent, "You walk southeast.");
            break;
        default:
            return;
            break;
    }

    MapCoordinate newPosition = deltaMapCoordiante(&gameState.player->position, deltaX, deltaY);

    if (isTraversable(gameState.map, newPosition)) {
        movePlayerCharacter(gameState.player, deltaX, deltaY);
    } else {
        initStoryEvent(&movementEvent, "You seem to have hit a wall.");
    }

    //pushStoryStack(gameState.storyEvents, movementEvent);

    updateVisibility(gameState.map, gameState.player->position, gameState.player->lightRadius);
}

/**
 *  Returns 1 of the proposed change in position would place the character on a wall tile. Returns 0 otherwise.
 */
/*static int isWall(Map* map, MapCoordinate position, int deltaX, int deltaY) {
    return map->tiles[position.y+deltaY][position.x+deltaX].isWall;
}*/


