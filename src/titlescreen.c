/**
 *  titlescreen.c - folly
 *
 *  This module shows an ncurses based title screen
 *
 */

#include <ncurses.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#include "ncwindow.h"
#include "randfolly.h"
#include "titlescreen.h"

static void* cycleEllipsis(void *maxPtr);
static void* cycleWander(void *maxPtr);
static void printFolly(int maxX);
static void printCell(int cell, int maxX);
static int randNextCell(int cell);

static pthread_t ellipsisThread;
static pthread_t wanderThread;
static pthread_mutex_t mutex;


/**
 * Displays a title screen in an infinite loop. The intent is that this will be called from a 
 * pthread.
 */
void displayTitleScreen(WINDOW *window) {

    initColors();
    pthread_mutex_init(&mutex, NULL);

    int maxX = 0;
    int maxY = 0;
    getmaxyx(window, maxY, maxX);

	clear();
    printFolly(maxX);
    	attron(COLOR_PAIR(WHITE_ON_BLACK));
    mvprintw(14, (maxX - 44)/2, "Press ENTER to continue...");
    	attroff(COLOR_PAIR(WHITE_ON_BLACK));
    move(0, 0);
    refresh();

    usleep(100000);

    unsigned int randomSeed = (unsigned int)time(NULL);
    initRandomSeed(randomSeed);

    int *arg = malloc(sizeof(*arg));
    *arg = maxX;
	pthread_create(&ellipsisThread, NULL, cycleEllipsis, arg);
	pthread_create(&wanderThread, NULL, cycleWander, arg);

    while (1) {
        pthread_mutex_lock(&mutex);
        move(0, 0);
        refresh();
        pthread_mutex_unlock(&mutex);

        usleep(10000);
    }
}

void termTitleScreenThreads() {
    pthread_cancel(ellipsisThread);
    pthread_cancel(wanderThread);
}

static void printFolly(int maxX) {
    attron(COLOR_PAIR(RED_ON_BLACK));
    mvprintw(5, (maxX - 44)/2, "   _____   _____    __       __     __  __");
    mvprintw(6, (maxX - 44)/2, " /\\_____\\ ) ___ (  /\\_\\     /\\_\\  /\\  /\\  /\\");
    mvprintw(7, (maxX - 44)/2, "( (  ___// /\\_/\\ \\( ( (    ( ( (  \\ \\ \\/ / /");
    mvprintw(8, (maxX - 44)/2, " \\ \\ \\_ / /_/ (_\\ \\\\ \\_\\    \\ \\_\\  \\ \\__/ /");
    mvprintw(9, (maxX - 44)/2, " / / /_\\\\ \\ )_/ / // / /__  / / /__ \\__/ /");
    mvprintw(10, (maxX - 44)/2, "/ /____/ \\ \\/_\\/ /( (_____(( (_____(/ / /");
    mvprintw(11, (maxX - 44)/2, "\\/_/      )_____(  \\/_____/ \\/_____/\\/_/");
    attroff(COLOR_PAIR(RED_ON_BLACK));
}

static void printCell(int cell, int maxX) {

    int x = (maxX - 44) / 2;

    attron(COLOR_PAIR(WHITE_ON_BLACK));
    switch (cell) {
        case 1:
            mvprintw(10, x, "/");
            mvprintw(11, x, "\\/");
            break;
        case 2:
            mvprintw(9, x, " /");
            mvprintw(10, x + 2, "/");
            break;
        case 3:
            mvprintw(9, x, " / /");
            break;
        case 4:
            mvprintw(8, x, " \\ \\");
            break;
        case 5:
            mvprintw(7, x, "( (");
            break;
        case 6:
            mvprintw(6, x, " /\\");
            mvprintw(7, x + 2, "(");
            break;
        case 7:
            mvprintw(5, x + 3, "_");
            mvprintw(6, x + 2, "\\__");
            break;
        case 8:
            mvprintw(5, x + 4, "__");
            mvprintw(6, x + 5, "__");
            break;
        case 9:
            mvprintw(5, x + 6, "__");
            mvprintw(6, x + 7, "_\\");
            break;
        case 10:
            mvprintw(6, x + 6, "__");
            mvprintw(7, x + 7, "_/");
            break;
        case 11:
            mvprintw(6, x + 4, "__");
            mvprintw(7, x + 5, "__");
            break;
        case 12:
            mvprintw(6, x + 3, "_");
            mvprintw(7, x + 2, "(");
            break;
        case 13:
            mvprintw(8, x + 3, "\\ \\");
            break;
        case 14:
            mvprintw(9, x + 3, "/ /");
            break;
        case 15:
            mvprintw(10, x + 2, "/__");
            break;
        case 16:
            mvprintw(10, x + 3, "__");
            mvprintw(11, x + 1, "/_/");
            break;
        case 17:
            mvprintw(9, x + 6, "_");
            mvprintw(10, x + 5, "__/");
            break;
        case 18:
            mvprintw(8, x + 6, "_");
            mvprintw(9, x + 6, "_\\");
            break;
        case 19:
            mvprintw(9, x + 8, "\\ \\");
            break;
        case 20:
            mvprintw(10, x + 9, "\\ \\");
            break;
        case 21:
            mvprintw(11, x + 10, ")__");
            break;
        case 22:
            mvprintw(10, x + 13, "_");
            mvprintw(11, x + 13, "_");
            break;
        case 23:
            mvprintw(11, x + 14, "__(");
            break;
        case 24:
            mvprintw(10, x + 15, "/ /");
            break;
        case 25:
            mvprintw(9, x + 16, "/ /");
            break;
        case 26:
            mvprintw(8, x + 16, "\\ \\");
            break;
        case 27:
            mvprintw(7, x + 15, "\\ \\");
            break;
        case 28:
            mvprintw(5, x + 14, "__");
            mvprintw(6, x + 14, "_ (");
            break;
        case 29:
            mvprintw(5, x + 13, "_");
            mvprintw(6, x + 13, "_");
            break;
        case 30:
            mvprintw(5, x + 10, "__");
            mvprintw(6, x + 10, ") _");
            break;
        case 31:
            mvprintw(7, x + 9, "/ /");
            break;
        case 32:
            mvprintw(8, x + 8, "/ /");
            break;
        case 33:
            mvprintw(7, x + 11, "/\\");
            mvprintw(8, x + 10, "/_/");
            break;
        case 34:
            mvprintw(8, x + 11, "_");
            mvprintw(9, x + 10, "\\ )");
            mvprintw(10, x + 11, "\\/");
            break;
        case 35:
            mvprintw(9, x + 13, "_");
            mvprintw(10, x + 12, "/_\\");
            break;
        case 36:
            mvprintw(8, x + 15, "_");
            mvprintw(9, x + 14, "/ /");
            mvprintw(10, x + 14, "\\/");
            break;
        case 37:
            mvprintw(7, x + 14, "/\\");
            mvprintw(8, x + 14, "(_\\");
            break;
        case 38:
            mvprintw(6, x + 12, "___");
            mvprintw(7, x + 12, "\\_/");
            break;
        case 39:
            mvprintw(5, x + 20, "__");
            mvprintw(6, x + 20, "\\_\\");
            break;
        case 40:
            mvprintw(6, x + 19, "/\\");
            mvprintw(7, x + 20, "(");
            break;
        case 41:
            mvprintw(7, x + 18, "( (");
            break;
        case 42:
            mvprintw(8, x + 19, "\\ \\");
            break;
        case 43:
            mvprintw(9, x + 19, "/ /");
            break;
        case 44:
            mvprintw(10, x + 18, "( (");
            break;
        case 45:
            mvprintw(10, x + 20, "(");
            mvprintw(11, x + 19, "\\/");
            break;
        case 46:
            mvprintw(10, x + 21, "__");
            mvprintw(11, x + 20, "/_");
            break;
        case 47:
            mvprintw(10, x + 23, "__");
            mvprintw(11, x + 22, "__");
            break;
        case 48:
            mvprintw(10, x + 25, "_");
            mvprintw(11, x + 24, "__/");
            break;
        case 49:
            mvprintw(9, x + 25, "_");
            mvprintw(10, x + 24, "__(");
            break;
        case 50:
            mvprintw(9, x + 24, "__");
            mvprintw(10, x + 22, "__");
            break;
        case 51:
            mvprintw(10, x + 20, "(__");
            break;
        case 52:
            mvprintw(8, x + 22, "_");
            mvprintw(9, x + 21, "/ /");
            break;
        case 53:
            mvprintw(8, x + 21, "\\_\\");
            break;
        case 54:
            mvprintw(6, x + 21, "_");
            mvprintw(7, x + 20, "( (");
            break;
        case 55:
            mvprintw(5, x + 29, "__");
            mvprintw(6, x + 29, "\\_\\");
            break;
        case 56:
            mvprintw(6, x + 28, "/\\");
            mvprintw(7, x + 29, "(");
            break;
        case 57:
            mvprintw(7, x + 27, "( (");
            break;
        case 58:
            mvprintw(8, x + 28, "\\ \\");
            break;
        case 59:
            mvprintw(9, x + 28, "/ /");
            break;
        case 60:
            mvprintw(10, x + 27, "( (");
            break;
        case 61:
            mvprintw(10, x + 29, "(");
            mvprintw(11, x + 28, "\\/");
            break;
        case 62:
            mvprintw(10, x + 30, "__");
            mvprintw(11, x + 29, "/_");
            break;
        case 63:
            mvprintw(10, x + 32, "__");
            mvprintw(11, x + 31, "__");
            break;
        case 64:
            mvprintw(10, x + 34, "_");
            mvprintw(11, x + 33, "__/");
            break;
        case 65:
            mvprintw(9, x + 34, "_");
            mvprintw(10, x + 33, "__(");
            break;
        case 66:
            mvprintw(9, x + 33, "__");
            mvprintw(10, x + 31, "__");
            break;
        case 67:
            mvprintw(10, x + 29, "(__");
            break;
        case 68:
            mvprintw(8, x + 31, "_");
            mvprintw(9, x + 30, "/ /");
            break;
        case 69:
            mvprintw(8, x + 30, "\\_\\");
            break;
        case 70:
            mvprintw(6, x + 30, "_");
            mvprintw(7, x + 29, "( (");
            break;
        case 71:
            mvprintw(6, x + 34, "/\\");
            mvprintw(7, x + 34, "\\");
            break;
        case 72:
            mvprintw(7, x + 36, "\\");
            mvprintw(8, x + 35, "\\");
            break;
        case 73:
            mvprintw(8, x + 37, "\\");
            mvprintw(9, x + 36, "\\");
            break;
        case 74:
            mvprintw(8, x + 38, "__");
            mvprintw(9, x + 37, "__/");
            break;
        case 75:
            mvprintw(10, x + 36, "/ /");
            break;
        case 76:
            mvprintw(10, x + 36, "/");
            mvprintw(11, x + 36, "\\/");
            break;
        case 77:
            mvprintw(11, x + 37, "/_/");
            break;
        case 78:
            mvprintw(10, x + 38, "/ /");
            break;
        case 79:
            mvprintw(9, x + 39, "/ /");
            break;
        case 80:
            mvprintw(8, x + 40, "/ /");
            break;
        case 81:
            mvprintw(7, x + 41, "/ /");
            break;
        case 82:
            mvprintw(6, x + 42, "/\\");
            mvprintw(7, x + 43, "/");
            break;
        case 83:
            mvprintw(5, x + 40, "__");
            mvprintw(6, x + 39, "\\  /");
            break;
        case 84:
            mvprintw(7, x + 39, "/ /");
            break;
        case 85:
            mvprintw(8, x + 37, "\\__/");
            break;
        case 86:
            mvprintw(7, x + 36, "\\ \\");
            break;
        case 87:
            mvprintw(5, x + 36, "__");
            mvprintw(6, x + 35, "\\  /");
            break;
        default:
            break;

    }
    attroff(COLOR_PAIR(WHITE_ON_BLACK));
}

static int randNextCell(int cell) {

    int r;
    switch (cell) {

        case 1:
            r = randUnif(0, 1);
            if (r == 0) {
                return 2;
            } else {
                return 16;
            }
            break;
        case 2:
            return randIntFromList(2, 1, 3);
        case 3:
            r = randUnif(0, 1);
            if (r == 0) {
                return 2;
            } else if (r == 1) {
                return 4;
            }
            break;
        case 4:
            r = randUnif(0, 1);
            if (r == 0) {
                return 3;
            } else if (r == 1) {
                return 5;
            }
            break;
        case 5:
            r = randUnif(0, 1);
            if (r == 0) {
                return 4;
            } else if (r == 1) {
                return 6;
            }
            break;
        case 6:
            r = randUnif(0, 1);
            if (r == 0) {
                return 5;
            } else if (r == 1) {
                return 7;
            }
            break;
        case 7:
            r = randUnif(0, 1);
            if (r == 0) {
                return 6;
            } else if (r == 1) {
                return 8;
            }
            break;
        case 8:
            r = randUnif(0, 1);
            if (r == 0) {
                return 7;
            } else if (r == 1) {
                return 9;
            }
            break;
        case 9:
            r = randUnif(0, 1);
            if (r == 0) {
                return 8;
            } else if (r == 1) {
                return 10;
            }
            break;
        case 10:
            r = randUnif(0, 1);
            if (r == 0) {
                return 9;
            } else if (r == 1) {
                return 31;
            }
            break;
        case 11:
            r = randUnif(0, 1);
            if (r == 0) {
                return 10;
            } else if (r == 1) {
                return 12;
            }
            break;
        case 12:
            r = randUnif(0, 1);
            if (r == 0) {
                return 11;
            } else if (r == 1) {
                return 13;
            }
            break;
        case 13:
            r = randUnif(0, 1);
            if (r == 0) {
                return 12;
            } else if (r == 1) {
                return 14;
            }
            break;
        case 14:
            r = randUnif(0, 1);
            if (r == 0) {
                return 13;
            } else if (r == 1) {
                return 15;
            }
            break;
        case 15:
            r = randUnif(0, 2);
            if (r == 0) {
                return 14;
            } else if (r == 1) {
                return 16;
            } else if (r == 2) {
                return 17;
            }
            break;
        case 16:
            r = randUnif(0, 1);
            if (r == 0) {
                return 1;
            } else if (r == 1) {
                return 15;
            }
            break;
        case 17:
            r = randUnif(0, 1);
            if (r == 0) {
                return 15;
            } else if (r == 1) {
                return 18;
            }
            break;
        case 18:
            r = randUnif(0, 1);
            if (r == 0) {
                return 17;
            } else if (r == 1) {
                return 19;
            }
            break;
        case 19:
            r = randUnif(0, 3);
            if (r == 0) {
                return 18;
            } else if (r == 1) {
                return 20;
            } else if (r == 2) {
                return 32;
            } else {
                return 34;
            }
            break;
        case 20:
            r = randUnif(0, 2);
            if (r == 0) {
                return 19;
            } else if (r == 1) {
                return 21;
            } else if (r == 2) {
                return 34;
            }
            break;
        case 21:
            r = randUnif(0, 2);
            if (r == 0) {
                return 20;
            } else if (r == 1) {
                return 22;
            } else if (r == 2) {
                return 35;
            }
            break;
        case 22:
            r = randUnif(0, 2);
            if (r == 0) {
                return 21;
            } else if (r == 1) {
                return 23;
            } else if (r == 2) {
                return 35;
            }
            break;
        case 23:
            r = randUnif(0, 2);
            if (r == 0) {
                return 22;
            } else if (r == 1) {
                return 24;
            } else if (r == 2) {
                return 35;
            }
            break;
        case 24:
            r = randUnif(0, 3);
            if (r == 0) {
                return 23;
            } else if (r == 1) {
                return 25;
            } else if (r == 2) {
                return 36;
            } else if (r == 3) {
                return 44;
            }
            break;
        case 25:
            r = randUnif(0, 3);
            if (r == 0) {
                return 24;
            } else if (r == 1) {
                return 26;
            } else if (r == 2) {
                return 36;
            } else if (r == 3) {
                return 43;
            }
            break;
        case 26:
            r = randUnif(0, 3);
            if (r == 0) {
                return 25;
            } else if (r == 1) {
                return 27;
            } else if (r == 2) {
                return 37;
            } else if (r == 3) {
                return 42;
            }
            break;
        case 27:
            r = randUnif(0, 3);
            if (r == 0) {
                return 26;
            } else if (r == 1) {
                return 28;
            } else if (r == 2) {
                return 37;
            } else if (r == 3) {
                return 41;
            }
            break;
        case 28:
            r = randUnif(0, 2);
            if (r == 0) {
                return 27;
            } else if (r == 1) {
                return 29;
            } else if (r == 2) {
                return 38;
            }
            break;
        case 29:
            r = randUnif(0, 2);
            if (r == 0) {
                return 28;
            } else if (r == 1) {
                return 30;
            } else if (r == 2) {
                return 38;
            }
            break;
        case 30:
            r = randUnif(0, 2);
            if (r == 0) {
                return 29;
            } else if (r == 1) {
                return 31;
            } else if (r == 2) {
                return 38;
            }
            break;
        case 31:
            r = randUnif(0, 3);
            if (r == 0) {
                return 30;
            } else if (r == 1) {
                return 32;
            } else if (r == 2) {
                return 33;
            } else if (r == 3) {
                return 10;
            }
            break;
        case 32:
            r = randUnif(0, 2);
            if (r == 0) {
                return 31;
            } else if (r == 1) {
                return 33;
            } else if (r == 2) {
                return 19;
            }
            break;
        case 33:
            r = randUnif(0, 3);
            if (r == 0) {
                return 31;
            } else if (r == 1) {
                return 32;
            } else if (r == 2) {
                return 34;
            } else if (r == 3) {
                return 38;
            }
            break;
        case 34:
            r = randUnif(0, 3);
            if (r == 0) {
                return 19;
            } else if (r == 1) {
                return 20;
            } else if (r == 2) {
                return 33;
            } else if (r == 3) {
                return 35;
            }
            break;
        case 35:
            r = randUnif(0, 4);
            if (r == 0) {
                return 34;
            } else if (r == 1) {
                return 36;
            } else if (r == 2) {
                return 21;
            } else if (r == 3) {
                return 22;
            } else if (r == 4) {
                return 23;
            }
            break;
        case 36:
            r = randUnif(0, 3);
            if (r == 0) {
                return 35;
            } else if (r == 1) {
                return 37;
            } else if (r == 2) {
                return 24;
            } else if (r == 3) {
                return 25;
            }
            break;
        case 37:
            r = randUnif(0, 3);
            if (r == 0) {
                return 36;
            } else if (r == 1) {
                return 38;
            } else if (r == 2) {
                return 26;
            } else if (r == 3) {
                return 27;
            }
            break;
        case 38:
            r = randUnif(0, 4);
            if (r == 0) {
                return 37;
            } else if (r == 1) {
                return 33;
            } else if (r == 2) {
                return 28;
            } else if (r == 3) {
                return 29;
            } else if (r == 4) {
                return 30;
            }
            break;
        case 39:
            r = randUnif(0, 1);
            if (r == 0) {
                return 40;
            } else if (r == 1) {
                return 54;
            }
            break;
        case 40:
            r = randUnif(0, 1);
            if (r == 0) {
                return 39;
            } else if (r == 1) {
                return 41;
            }
            break;
        case 41:
            r = randUnif(0, 2);
            if (r == 0) {
                return 40;
            } else if (r == 1) {
                return 42;
            } else if (r == 2) {
                return 27;
            }
            break;
        case 42:
            r = randUnif(0, 2);
            if (r == 0) {
                return 41;
            } else if (r == 1) {
                return 43;
            } else if (r == 2) {
                return 26;
            }
            break;
        case 43:
            r = randUnif(0, 2);
            if (r == 0) {
                return 42;
            } else if (r == 1) {
                return 44;
            } else if (r == 2) {
                return 25;
            }
            break;
        case 44:
            r = randUnif(0, 2);
            if (r == 0) {
                return 43;
            } else if (r == 1) {
                return 45;
            } else if (r == 2) {
                return 24;
            }
            break;
        case 45:
            r = randUnif(0, 1);
            if (r == 0) {
                return 44;
            } else if (r == 1) {
                return 46;
            }
            break;
        case 46:
            r = randUnif(0, 1);
            if (r == 0) {
                return 45;
            } else if (r == 1) {
                return 47;
            }
            break;
        case 47:
            r = randUnif(0, 1);
            if (r == 0) {
                return 46;
            } else if (r == 1) {
                return 48;
            }
            break;
        case 48:
            r = randUnif(0, 1);
            if (r == 0) {
                return 47;
            } else if (r == 1) {
                return 49;
            }
            break;
        case 49:
            r = randUnif(0, 2);
            if (r == 0) {
                return 48;
            } else if (r == 1) {
                return 50;
            } else if (r == 2) {
                return 60;
            }
            break;
        case 50:
            r = randUnif(0, 1);
            if (r == 0) {
                return 49;
            } else if (r == 1) {
                return 51;
            }
            break;
        case 51:
            r = randUnif(0, 1);
            if (r == 0) {
                return 50;
            } else if (r == 1) {
                return 52;
            }
            break;
        case 52:
            r = randUnif(0, 1);
            if (r == 0) {
                return 51;
            } else if (r == 1) {
                return 53;
            }
            break;
        case 53:
            r = randUnif(0, 1);
            if (r == 0) {
                return 52;
            } else if (r == 1) {
                return 54;
            }
            break;
        case 54:
            r = randUnif(0, 1);
            if (r == 0) {
                return 53;
            } else if (r == 1) {
                return 39;
            }
            break;
        case 55:
            r = randUnif(0, 1);
            if (r == 0) {
                return 56;
            } else if (r == 1) {
                return 70;
            }
            break;
        case 56:
            r = randUnif(0, 1);
            if (r == 0) {
                return 55;
            } else if (r == 1) {
                return 57;
            }
            break;
        case 57:
            r = randUnif(0, 1);
            if (r == 0) {
                return 56;
            } else if (r == 1) {
                return 58;
            }
            break;
        case 58:
            r = randUnif(0, 1);
            if (r == 0) {
                return 57;
            } else if (r == 1) {
                return 59;
            }
            break;
        case 59:
            r = randUnif(0, 1);
            if (r == 0) {
                return 58;
            } else if (r == 1) {
                return 60;
            }
            break;
        case 60:
            r = randUnif(0, 2);
            if (r == 0) {
                return 59;
            } else if (r == 1) {
                return 61;
            } else if (r == 2) {
                return 49;
            }
            break;
        case 61:
            r = randUnif(0, 1);
            if (r == 0) {
                return 60;
            } else if (r == 1) {
                return 62;
            }
            break;
        case 62:
            r = randUnif(0, 1);
            if (r == 0) {
                return 61;
            } else if (r == 1) {
                return 63;
            }
            break;
        case 63:
            r = randUnif(0, 1);
            if (r == 0) {
                return 62;
            } else if (r == 1) {
                return 64;
            }
            break;
        case 64:
            r = randUnif(0, 2);
            if (r == 0) {
                return 63;
            } else if (r == 1) {
                return 65;
            } else if (r == 2) {
                return 76;
            }
            break;
        case 65:
            r = randUnif(0, 2);
            if (r == 0) {
                return 64;
            } else if (r == 1) {
                return 66;
            } else if (r == 2) {
                return 75;
            }
            break;
        case 66:
            r = randUnif(0, 1);
            if (r == 0) {
                return 65;
            } else if (r == 1) {
                return 67;
            }
            break;
        case 67:
            r = randUnif(0, 1);
            if (r == 0) {
                return 66;
            } else if (r == 1) {
                return 68;
            }
            break;
        case 68:
            r = randUnif(0, 1);
            if (r == 0) {
                return 67;
            } else if (r == 1) {
                return 69;
            }
            break;
        case 69:
            r = randUnif(0, 1);
            if (r == 0) {
                return 68;
            } else if (r == 1) {
                return 70;
            }
            break;
        case 70:
            r = randUnif(0, 1);
            if (r == 0) {
                return 69;
            } else if (r == 1) {
                return 55;
            }
            break;
        case 71:
            r = randUnif(0, 1);
            if (r == 0) {
                return 87;
            } else if (r == 1) {
                return 72;
            }
            break;
        case 72:
            r = randUnif(0, 1);
            if (r == 0) {
                return 71;
            } else if (r == 1) {
                return 73;
            }
            break;
        case 73:
            r = randUnif(0, 1);
            if (r == 0) {
                return 72;
            } else if (r == 1) {
                return 74;
            }
            break;
        case 74:
            r = randUnif(0, 1);
            if (r == 0) {
                return 73;
            } else if (r == 1) {
                return 79;
            }
            break;
        case 75:
            r = randUnif(0, 1);
            if (r == 0) {
                return 65;
            } else if (r == 1) {
                return 76;
            }
            break;
        case 76:
            r = randUnif(0, 2);
            if (r == 0) {
                return 75;
            } else if (r == 1) {
                return 77;
            } else if (r == 2) {
                return 64;
            }
            break;
        case 77:
            r = randUnif(0, 1);
            if (r == 0) {
                return 76;
            } else if (r == 1) {
                return 78;
            }
            break;
        case 78:
            r = randUnif(0, 1);
            if (r == 0) {
                return 77;
            } else if (r == 1) {
                return 79;
            }
            break;
        case 79:
            r = randUnif(0, 2);
            if (r == 0) {
                return 74;
            } else if (r == 1) {
                return 78;
            } else if (r == 2) {
                return 80;
            }
            break;
        case 80:
            r = randUnif(0, 1);
            if (r == 0) {
                return 79;
            } else if (r == 1) {
                return 81;
            }
            break;
        case 81:
            r = randUnif(0, 1);
            if (r == 0) {
                return 80;
            } else if (r == 1) {
                return 82;
            }
            break;
        case 82:
            r = randUnif(0, 1);
            if (r == 0) {
                return 81;
            } else if (r == 1) {
                return 83;
            }
            break;
        case 83:
            r = randUnif(0, 1);
            if (r == 0) {
                return 82;
            } else if (r == 1) {
                return 84;
            }
            break;
        case 84:
            r = randUnif(0, 1);
            if (r == 0) {
                return 83;
            } else if (r == 1) {
                return 85;
            }
            break;
        case 85:
            r = randUnif(0, 1);
            if (r == 0) {
                return 84;
            } else if (r == 1) {
                return 86;
            }
            break;
        case 86:
            r = randUnif(0, 1);
            if (r == 0) {
                return 85;
            } else if (r == 1) {
                return 87;
            }
            break;
        case 87:
            r = randUnif(0, 1);
            if (r == 0) {
                return 86;
            } else if (r == 1) {
                return 71;
            }
            break;
        default:
            return 1;
            break;

    }
    return 1;
}

static void* cycleEllipsis(void *maxPtr) {
    int maxX = *((int *) maxPtr);

    while (1) {
        pthread_mutex_lock(&mutex);
        mvprintw(14, (maxX - 44)/2 + 23, "   ");
        move(0, 0);
        pthread_mutex_unlock(&mutex);

        usleep(800000);

        pthread_mutex_lock(&mutex);
        mvprintw(14, (maxX - 44)/2 + 23, ".  ");
        move(0, 0);
        pthread_mutex_unlock(&mutex);

        usleep(600000);

        pthread_mutex_lock(&mutex);
        mvprintw(14, (maxX - 44)/2 + 23, ".. ");
        move(0, 0);
        pthread_mutex_unlock(&mutex);

        usleep(400000);

        pthread_mutex_lock(&mutex);
        mvprintw(14, (maxX - 44)/2 + 23, "...");
        move(0, 0);
        pthread_mutex_unlock(&mutex);

        usleep(1200000);
    }
    return NULL;
}

static void* cycleWander(void *maxPtr) {
    int maxX = *((int *) maxPtr);

    int index = 2;//randUnif(1, 87);
    int sleepFor = 0;
    while (1) {

        index = randNextCell(index);

        pthread_mutex_lock(&mutex);
        printFolly(maxX);
        printCell(index, maxX);
        sleepFor = randUnif(0, 4);
        move(0, 0);
        pthread_mutex_unlock(&mutex);

        if (sleepFor == 0) {
            usleep(250000);
        } else if (sleepFor == 1) {
            usleep(450000);
        } else if (sleepFor == 2) {
            usleep(500000);
        } else if (sleepFor == 3) {
            usleep(550000);
        } else {
            usleep(1250000);
        }
    }

    return NULL;
}



