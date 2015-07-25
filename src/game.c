#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>

#include "game.h"
#include "ncwindow.h"

void initColors() {
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK); // 1 - white on black
	init_pair(2, COLOR_BLUE, COLOR_BLACK);  // 2 - blue on black
	init_pair(3, COLOR_RED, COLOR_BLACK);   // 3 - red on black
}

void displayHelpScreen(WINDOW *menu_win) {

    clear();
	mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
	refresh();
}

void displayDeathScreen(WINDOW *menu_win) {
    /*printf("You have died.\n");
    printf("\n");
    printf("\n");*/
}

void updateGameState(int input, gameState *game) {
		switch(input) {
            case 'k':
            case KEY_UP:
                game->moveDir = 0;
                game->playerPosition.y -= 1;
				break;
            case 'j':
			case KEY_DOWN:
                game->moveDir = 4;
                game->playerPosition.y += 1;
				break;
            case 'h':
			case KEY_LEFT:
                game->moveDir = 6;
                game->playerPosition.x -= 1;
				break;
            case 'l':
			case KEY_RIGHT:
                game->moveDir = 2;
                game->playerPosition.x += 1;
				break;
            case 'y':
                game->moveDir = 7;
                game->playerPosition.y -= 1;
                game->playerPosition.x -= 1;
				break;
            case 'u':
                game->moveDir = 1;
                game->playerPosition.y -= 1;
                game->playerPosition.x += 1;
				break;
            case 'b':
                game->moveDir = 5;
                game->playerPosition.y += 1;
                game->playerPosition.x -= 1;
				break;
            case 'n':
                game->moveDir = 3;
                game->playerPosition.y += 1;
                game->playerPosition.x += 1;
				break;
			default:
                game->moveDir = 8;
				break;
		}

        if (game->playerPosition.x > game->maximumPosition.x) {
            game->playerPosition.x = game->maximumPosition.x;
        } else if (game->playerPosition.x < 0) {
            game->playerPosition.x = 0;
        }

        if (game->playerPosition.y > game->maximumPosition.y) {
            game->playerPosition.y = game->maximumPosition.y;
        } else if (game->playerPosition.y < 0) {
            game->playerPosition.y = 0;
        }
}

void displayGameScreen(WINDOW *menu_win, gameState *game) {

    clear();

    	attron(COLOR_PAIR(3));
	switch(game->moveDir) {
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
    mvprintw(game->playerPosition.y, game->playerPosition.x, "@");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(1));

    wmove(menu_win, game->maximumPosition.y, game->maximumPosition.x);

    usleep(DELAY);
    refresh();
}


