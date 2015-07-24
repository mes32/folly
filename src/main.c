#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>

#define WIDTH 100
#define HEIGHT 100
#define DELAY 30000

typedef struct coordinates coordinates;
struct coordinates {
    int x;
    int y;
};

typedef struct gameState gameState;
struct gameState {
    //WINDOW* menu_win;
    //int moveDir;
    coordinates playerPosition;
    //coordinates maximumPosition;
};

void showTitleScreen(char* version);
void showHelpScreen();
void showGameOverScreen();

void updateGameState();

WINDOW* openGameWindow();
void refreshGameWindow(WINDOW* menu_win, int moveDir, coordinates playerPosition, coordinates maximumPosition);
void closeGameWindow();

int main() {

    char* VERSION = "0.1";
    showTitleScreen(VERSION);

    showHelpScreen();

    // ****

	WINDOW *menu_win = openGameWindow();

    curs_set(FALSE);
	mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
	refresh();

	int c;
    int moveDir = 0;
    coordinates playerPosition = {10, 10};
    int x = 10, y = 10;

    coordinates maximumPosition = {12, 12};
    int xMax = 12, yMax = 12;

	while(1) {
        c = wgetch(menu_win);
		switch(c) {
            case 'k':
            case KEY_UP:
                moveDir = 0;
                y -= 1;
                playerPosition.y -= 1;
				break;
            case 'j':
			case KEY_DOWN:
                moveDir = 4;
                y += 1;
                playerPosition.y += 1;
				break;
            case 'h':
			case KEY_LEFT:
                moveDir = 6;
                x -= 1;
                playerPosition.x -= 1;
				break;
            case 'l':
			case KEY_RIGHT:
                moveDir = 2;
                x += 1;
                playerPosition.x += 1;
				break;
            case 'y':
                moveDir = 7;
                y -= 1;
                x -= 1;
                playerPosition.y -= 1;
                playerPosition.x -= 1;
				break;
            case 'u':
                moveDir = 1;
                y -= 1;
                x += 1;
                playerPosition.y -= 1;
                playerPosition.x += 1;
				break;
            case 'b':
                moveDir = 5;
                y += 1;
                x -= 1;
                playerPosition.y += 1;
                playerPosition.x -= 1;
				break;
            case 'n':
                moveDir = 3;
                y += 1;
                x += 1;
                playerPosition.y += 1;
                playerPosition.x += 1;
				break;
			default:
                moveDir = 8;
				break;
		}

        if (x > xMax) {
            x = xMax;
        } else if (x < 0) {
            x = 0;
        }

        if (y > yMax) {
            y = yMax;
        } else if (y < 0) {
            y = 0;
        }

        if (playerPosition.x > maximumPosition.x) {
            playerPosition.x = maximumPosition.x;
        } else if (playerPosition.x < 0) {
            playerPosition.x = 0;
        }

        if (playerPosition.y > maximumPosition.y) {
            playerPosition.y = maximumPosition.y;
        } else if (playerPosition.y < 0) {
            playerPosition.y = 0;
        }

        refreshGameWindow(menu_win, moveDir, playerPosition, maximumPosition);

	}

    closeGameWindow();

    // *****

    showGameOverScreen();

	return 0;
}

void showTitleScreen(char* version) {
    printf("\n");
    printf("Starting Folly v%s\n", version);
    printf("\n");
    printf("       _____   _____    __       __     __  __   \n");
    printf("     /\\_____\\ ) ___ (  /\\_\\     /\\_\\  /\\  /\\  /\\ \n");
    printf("    ( (  ___// /\\_/\\ \\( ( (    ( ( (  \\ \\ \\/ / / \n");
    printf("     \\ \\ \\_ / /_/ (_\\ \\\\ \\_\\    \\ \\_\\  \\ \\__/ /  \n");
    printf("     / / /_\\\\ \\ )_/ / // / /__  / / /__ \\__/ /   \n");
    printf("    / /____/ \\ \\/_\\/ /( (_____(( (_____(/ / /    \n");
    printf("    \\/_/      )_____(  \\/_____/ \\/_____/\\/_/     \n");
    printf("\n");
    printf("\n");
    printf("Press enter key to continue...\n");

    getchar();
}

void showHelpScreen() {
    /*printf("HELP SCREEN\n");
    printf("\n");
    printf("\n");
    printf("Press any key to continue...\n");

    int keypress = getchar();*/
}

void showGameOverScreen() {
    /*printf("You have died.\n");
    printf("\n");
    printf("\n");*/
}

void updateGameState() {

}

WINDOW* openGameWindow() {

	initscr();
	noecho();
    curs_set(FALSE);
	cbreak();	// Line buffering disabled. Pass on everything

	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
		
	WINDOW *menu_win;
	menu_win = newwin(HEIGHT, WIDTH, HEIGHT, WIDTH);
	keypad(menu_win, TRUE);
	clear();

    return menu_win;
}

void refreshGameWindow(WINDOW* menu_win, int moveDir, coordinates playerPosition, coordinates maximumPosition) {

    clear();

    	attron(COLOR_PAIR(3));
	switch(moveDir) {
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
    mvprintw(playerPosition.y, playerPosition.x, "@");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(1));

    wmove(menu_win, maximumPosition.y, maximumPosition.x);

    usleep(DELAY);
    refresh();
}

void closeGameWindow() {
	clrtoeol();
	refresh();
	endwin();
}
