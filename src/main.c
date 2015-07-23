#include <stdio.h>
#include <ncurses.h>

#define WIDTH 100
#define HEIGHT 100
#define DELAY 30000

void showTitleScreen(char* version);
void showHelpScreen();
void showGameOverScreen();

int main() {

    char* VERSION = "0.1";
    showTitleScreen(VERSION);

    showHelpScreen();


    // ****

	WINDOW *menu_win;
	initscr();
	clear();
	noecho();
    curs_set(FALSE);
	cbreak();	// Line buffering disabled. Pass on everything
		
	menu_win = newwin(HEIGHT, WIDTH, HEIGHT, WIDTH);
	keypad(menu_win, TRUE);
	clear();
	mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
	refresh();

	int c;
    int x = 10, y = 10;
    int xMax = 100, yMax = 100;

	start_color(); // Start color
    init_color(COLOR_RED, 0, 0, 0);
    init_color(COLOR_BLUE, 200, 200, 200);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);

	while(1) {
        c = wgetch(menu_win);
        clear();
		switch(c) {

            case 'k':
            case KEY_UP:
		        mvprintw(0, 0, "UP");
                y -= 1;
				break;
            case 'j':
			case KEY_DOWN:
      attron(A_BOLD);
		        mvprintw(0, 0, "DOWN");
      attroff(A_BOLD);
                y += 1;
				break;
            case 'h':
			case KEY_LEFT:
		        mvprintw(0, 0, "LEFT");
                x -= 1;
				break;
            case 'l':
			case KEY_RIGHT:
		        mvprintw(0, 0, "RIGHT");
                x += 1;
				break;
            case 'y':
		        mvprintw(0, 0, "UP LEFT");
                y -= 1;
                x -= 1;
				break;
            case 'u':
		        mvprintw(0, 0, "UP RIGHT");
                y -= 1;
                x += 1;
				break;
            case 'b':
		        mvprintw(0, 0, "DOWN LEFT");
                y += 1;
                x -= 1;
				break;
            case 'n':
		        mvprintw(0, 0, "DOWN RIGHT");
                y += 1;
                x += 1;
				break;

			default:
				mvprintw(0, 0, "OTHER");
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

	    //attron(COLOR_PAIR(2));
      //attron(A_BOLD);
        //mvprintw(y-4, x, "#################");
      //attroff(A_BOLD);
        //mvprintw(y-3, x, "#################");


        //mvprintw(y, x-2, "#");
      attron(A_BOLD);
        mvprintw(y, x, "@");
      attroff(A_BOLD);
	    attroff(COLOR_PAIR(2));
	    //attron(COLOR_PAIR(1));
        //mvprintw(y, x+2, "o");
        //mvprintw(y, x+4, "s");
        //mvprintw(y, x+8, "O");
        //mvprintw(y, x+10, "S");

	    attroff(COLOR_PAIR(1));


        wmove(menu_win, yMax, xMax);

        usleep(DELAY);
        refresh();


	}

	clrtoeol();
	refresh();
	endwin();

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

    int keypress = getchar();
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
