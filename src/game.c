#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include "game.h"
#include "ncwindow.h"

static const int DELAY = 30000;

static WINDOW* window;
static GameState gameState;

static void initColors();
static void displayHelpScreen();
static void displayGameScreen();
static void initGameState();
static void updateGameState(int input);

void initGame(WINDOW* ncursesWindow) {
    window = ncursesWindow;
    initGameState();
}

void runGame() {
    initColors();

    displayHelpScreen();

    int c;
	while(1) {
        c = wgetch(window);
        updateGameState(c);
        displayGameScreen();
	}
}

static void initColors() {
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK); // 1 - white on black
	init_pair(2, COLOR_BLUE, COLOR_BLACK);  // 2 - blue on black
	init_pair(3, COLOR_RED, COLOR_BLACK);   // 3 - red on black
}

static void displayHelpScreen() {
    clear();
	mvprintw(0, 0, "Use arrow keys to move around");
	refresh();
}

static void displayGameScreen() {
    clear();

    	attron(COLOR_PAIR(3));
	switch(gameState.moveDir) {
        case 0:
            mvprintw(0, 0, "UP");
            break;
        case 4:
            mvprintw(0, 0, "DOWN");
            break;
        case 6:
            mvprintw(0, 0, "LEFT");
            break;
        case 2:
            mvprintw(0, 0, "RIGHT");
            break;
        case 7:
        	    mvprintw(0, 0, "UP LEFT");
            break;
        case 1:
            mvprintw(0, 0, "UP RIGHT");
            break;
        case 5:
            mvprintw(0, 0, "DOWN LEFT");
            break;
        case 3:
            mvprintw(0, 0, "DOWN RIGHT");
            break;
        case 8:
            mvprintw(0, 0, "OTHER");
            break;
        default:
            mvprintw(0, 0, "UNKNOWN");
    }
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(1));
    attron(A_BOLD);
    mvprintw(gameState.playerPosition.y, gameState.playerPosition.x, "@");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(1));

    wmove(window, gameState.maximumPosition.y, gameState.maximumPosition.x);

    usleep(DELAY);
    refresh();
}

static void initGameState() {
    Coordinates playerPosition = {1, 1};
    Coordinates maximumPosition = {12, 12};

    gameState.moveDir = 0;
    gameState.playerPosition = playerPosition;
    gameState.maximumPosition = maximumPosition;
}

static void updateGameState(int input) {
		switch(input) {
            case 'k':
            case KEY_UP:
                gameState.moveDir = 0;
                gameState.playerPosition.y -= 1;
				break;
            case 'j':
			case KEY_DOWN:
                gameState.moveDir = 4;
                gameState.playerPosition.y += 1;
				break;
            case 'h':
			case KEY_LEFT:
                gameState.moveDir = 6;
                gameState.playerPosition.x -= 1;
				break;
            case 'l':
			case KEY_RIGHT:
                gameState.moveDir = 2;
                gameState.playerPosition.x += 1;
				break;
            case 'y':
                gameState.moveDir = 7;
                gameState.playerPosition.y -= 1;
                gameState.playerPosition.x -= 1;
				break;
            case 'u':
                gameState.moveDir = 1;
                gameState.playerPosition.y -= 1;
                gameState.playerPosition.x += 1;
				break;
            case 'b':
                gameState.moveDir = 5;
                gameState.playerPosition.y += 1;
                gameState.playerPosition.x -= 1;
				break;
            case 'n':
                gameState.moveDir = 3;
                gameState.playerPosition.y += 1;
                gameState.playerPosition.x += 1;
				break;
			default:
                gameState.moveDir = 8;
				break;
		}

        if (gameState.playerPosition.x > gameState.maximumPosition.x) {
            gameState.playerPosition.x = gameState.maximumPosition.x;
        } else if (gameState.playerPosition.x < 0) {
            gameState.playerPosition.x = 0;
        }

        if (gameState.playerPosition.y > gameState.maximumPosition.y) {
            gameState.playerPosition.y = gameState.maximumPosition.y;
        } else if (gameState.playerPosition.y < 0) {
            gameState.playerPosition.y = 0;
        }
}


