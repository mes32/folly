/**
 *  titlescreen.c - folly
 *
 *  This module shows an ncurses based title screen
 *
 */

#include <ncurses.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "ncwindow.h"
#include "titlescreen.h"

static void* cycleEllipsis(void *maxPtr);
static void* cycleWander(void *maxPtr);
static void printFolly(int maxX);
static void printCell(int cell, int maxX);

static pthread_t ellipsisThread;
static pthread_t wanderThread;

/**
 * Displays a title screen in an infinite loop. The intent is that this will be called from a 
 * pthread.
 */
void displayTitleScreen(WINDOW *window) {

	clear();

    initColors();

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

    int *arg = malloc(sizeof(*arg));
    *arg = maxX;
	//pthread_create(&ellipsisThread, NULL, cycleEllipsis, arg);

	pthread_create(&wanderThread, NULL, cycleWander, arg);

    /*while (1) {
        move(0, 0);
        refresh();
        usleep(10000);
    }*/
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
            mvprintw(8, x + 6, "_");
            mvprintw(9, x + 6, "_\\");
            break;
        case 20:
            mvprintw(9, x + 8, "\\ \\");
            break;
        case 21:
            mvprintw(10, x + 9, "\\ \\");
            break;
        case 22:
            mvprintw(11, x + 10, ")__");
            break;
        case 23:
            mvprintw(10, x + 13, "_");
            mvprintw(11, x + 13, "_");
            break;
        case 24:
            mvprintw(11, x + 14, "__(");
            break;
        case 25:
            mvprintw(10, x + 15, "/ /");
            break;
        case 26:
            mvprintw(9, x + 16, "/ /");
            break;
        case 27:
            mvprintw(8, x + 16, "\\ \\");
            break;
        case 28:
            mvprintw(7, x + 15, "\\ \\");
            break;
        case 29:
            mvprintw(5, x + 14, "__");
            mvprintw(6, x + 14, "_ (");
            break;
        case 30:
            mvprintw(5, x + 13, "_");
            mvprintw(6, x + 13, "_");
            break;
        case 31:
            mvprintw(5, x + 10, "__");
            mvprintw(6, x + 10, ") _");
            break;
        case 32:
            mvprintw(7, x + 9, "/ /");
            break;
        case 33:
            mvprintw(8, x + 8, "/ /");
            break;
        case 34:
            mvprintw(7, x + 11, "/\\");
            mvprintw(8, x + 10, "/_/");
            break;
        case 35:
            mvprintw(8, x + 11, "_");
            mvprintw(9, x + 10, "\\ )");
            mvprintw(10, x + 11, "\\/");
            break;
        case 36:
            mvprintw(9, x + 13, "_");
            mvprintw(10, x + 12, "/_\\");
            break;
        case 37:
            mvprintw(8, x + 15, "_");
            mvprintw(9, x + 14, "/ /");
            mvprintw(10, x + 14, "\\/");
            break;
        case 38:
            mvprintw(7, x + 14, "/\\");
            mvprintw(8, x + 14, "(_\\");
            break;
        case 39:
            mvprintw(6, x + 12, "___");
            mvprintw(7, x + 12, "\\_/");
            break;
        case 40:
            mvprintw(5, x + 20, "__");
            mvprintw(6, x + 20, "\\_\\");
            break;
        case 41:
            mvprintw(6, x + 19, "/\\");
            mvprintw(7, x + 20, "(");
            break;
        case 42:
            mvprintw(7, x + 18, "( (");
            break;
        case 43:
            mvprintw(8, x + 19, "\\ \\");
            break;
        case 44:
            mvprintw(9, x + 19, "/ /");
            break;
        case 45:
            mvprintw(10, x + 18, "( (");
            break;
        case 46:
            mvprintw(10, x + 20, "(");
            mvprintw(11, x + 19, "\\/");
            break;
        case 47:
            mvprintw(10, x + 21, "__");
            mvprintw(11, x + 20, "/_");
            break;
        case 48:
            mvprintw(10, x + 23, "__");
            mvprintw(11, x + 22, "__");
            break;
        case 49:
            mvprintw(10, x + 25, "_");
            mvprintw(11, x + 24, "__/");
            break;
        case 50:
            mvprintw(9, x + 25, "_");
            mvprintw(10, x + 24, "__(");
            break;
        case 51:
            mvprintw(9, x + 24, "__");
            mvprintw(10, x + 22, "__");
            break;
        case 52:
            mvprintw(10, x + 20, "(__");
            break;
        case 53:
            mvprintw(8, x + 22, "_");
            mvprintw(9, x + 21, "/ /");
            break;
        case 54:
            mvprintw(8, x + 21, "\\_\\");
            break;
        case 55:
            mvprintw(6, x + 21, "_");
            mvprintw(7, x + 20, "( (");
            break;
        case 56:
            mvprintw(5, x + 29, "__");
            mvprintw(6, x + 29, "\\_\\");
            break;
        case 57:
            mvprintw(6, x + 28, "/\\");
            mvprintw(7, x + 29, "(");
            break;
        case 58:
            mvprintw(7, x + 27, "( (");
            break;
        case 59:
            mvprintw(8, x + 28, "\\ \\");
            break;
        case 60:
            mvprintw(9, x + 28, "/ /");
            break;
        case 61:
            mvprintw(10, x + 27, "( (");
            break;
        case 62:
            mvprintw(10, x + 29, "(");
            mvprintw(11, x + 28, "\\/");
            break;
        case 63:
            mvprintw(10, x + 30, "__");
            mvprintw(11, x + 29, "/_");
            break;
        case 64:
            mvprintw(10, x + 32, "__");
            mvprintw(11, x + 31, "__");
            break;
        case 65:
            mvprintw(10, x + 34, "_");
            mvprintw(11, x + 33, "__/");
            break;
        case 66:
            mvprintw(9, x + 34, "_");
            mvprintw(10, x + 33, "__(");
            break;
        case 67:
            mvprintw(9, x + 33, "__");
            mvprintw(10, x + 31, "__");
            break;
        case 68:
            mvprintw(10, x + 29, "(__");
            break;
        case 69:
            mvprintw(8, x + 31, "_");
            mvprintw(9, x + 30, "/ /");
            break;
        case 70:
            mvprintw(8, x + 30, "\\_\\");
            break;
        case 71:
            mvprintw(6, x + 30, "_");
            mvprintw(7, x + 29, "( (");
            break;
        case 72:
            mvprintw(6, x + 34, "/\\");
            mvprintw(7, x + 34, "\\");
            break;
        case 73:
            mvprintw(7, x + 36, "\\");
            mvprintw(8, x + 35, "\\");
            break;
        case 74:
            mvprintw(8, x + 37, "\\");
            mvprintw(9, x + 36, "\\");
            break;
        case 75:
            mvprintw(8, x + 38, "__");
            mvprintw(9, x + 37, "__/");
            break;
        case 76:
            mvprintw(9, x + 37, "__");
            mvprintw(10, x + 36, "/ /");
            break;
        case 77:
            mvprintw(10, x + 36, "/");
            mvprintw(11, x + 36, "\\/");
            break;
        case 78:
            mvprintw(11, x + 37, "/_/");
            break;
        case 79:
            mvprintw(10, x + 38, "/ /");
            break;
        case 80:
            mvprintw(9, x + 39, "/ /");
            break;
        case 81:
            mvprintw(8, x + 40, "/ /");
            break;
        case 82:
            mvprintw(7, x + 41, "/ /");
            break;
        case 83:
            mvprintw(6, x + 42, "/\\");
            mvprintw(7, x + 43, "/");
            break;
        case 84:
            mvprintw(5, x + 40, "__");
            mvprintw(6, x + 39, "\\  /");
            break;
        case 85:
            mvprintw(7, x + 39, "/ /");
            break;
        case 86:
            mvprintw(8, x + 37, "\\__/");
            break;
        case 87:
            mvprintw(7, x + 36, "\\ \\");
            break;
        case 88:
            mvprintw(5, x + 36, "__");
            mvprintw(6, x + 35, "\\  /");
            break;
        default:
            break;

    }
    attroff(COLOR_PAIR(WHITE_ON_BLACK));
}

static void* cycleEllipsis(void *maxPtr) {
    int maxX = *((int *) maxPtr);

    while (1) {
        mvprintw(14, (maxX - 44)/2 + 23, "   ");
        //move(0, 0);
        //refresh();
        usleep(400000);
        mvprintw(14, (maxX - 44)/2 + 23, ".  ");
        //move(0, 0);
        //refresh();
        usleep(300000);
        mvprintw(14, (maxX - 44)/2 + 23, ".. ");
        //move(0, 0);
        //refresh();
        usleep(200000);
        mvprintw(14, (maxX - 44)/2 + 23, "...");
        //move(0, 0);
        //refresh();
        usleep(600000);
    }
    return NULL;
}

static void* cycleWander(void *maxPtr) {
    int maxX = *((int *) maxPtr);

    int index = 1;
    while (1) {
        if (index > 88) {
            index = 1;
        }
        printFolly(maxX);
        printCell(index, maxX);
        move(0, 0);
        refresh();
        usleep(500000);
        index++;
    }

    return NULL;
}



