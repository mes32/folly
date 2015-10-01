/**
 *  titlescreen.c - folly
 *
 *  This module shows an ncurses based title screen
 *
 */

#include <assert.h>
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
            assert(0);
    }
    attroff(COLOR_PAIR(WHITE_ON_BLACK));
}

static int randNextCell(int cell) {

    int r;
    switch (cell) {

        case 1:
            return randIntFromList(2, 2, 16);
        case 2:
            return randIntFromList(2, 1, 3);
        case 3:
            return randIntFromList(2, 2, 4);
        case 4:
            return randIntFromList(2, 3, 5);
        case 5:
            return randIntFromList(2, 4, 6);
        case 6:
            return randIntFromList(2, 5, 7);
        case 7:
            return randIntFromList(2, 6, 8);
        case 8:
            return randIntFromList(2, 7, 9);
        case 9:
            return randIntFromList(2, 8, 10);
        case 10:
            return randIntFromList(2, 9, 31);
        case 11:
            return randIntFromList(2, 10, 12);
        case 12:
            return randIntFromList(2, 11, 13);
        case 13:
            return randIntFromList(2, 12, 14);
        case 14:
            return randIntFromList(2, 13, 15);
        case 15:
            return randIntFromList(3, 14, 16, 17);
        case 16:
            return randIntFromList(2, 1, 15);
        case 17:
            return randIntFromList(2, 15, 18);
        case 18:
            return randIntFromList(2, 17, 19);
        case 19:
            return randIntFromList(4, 18, 20, 32, 34);
        case 20:
            return randIntFromList(3, 19, 21, 34);
        case 21:
            return randIntFromList(3, 20, 22, 35);
        case 22:
            return randIntFromList(3, 21, 23, 35);
        case 23:
            return randIntFromList(3, 22, 24, 35);
        case 24:
            return randIntFromList(4, 23, 25, 36, 44);
        case 25:
            return randIntFromList(4, 24, 26, 36, 43);
        case 26:
            return randIntFromList(4, 25, 27, 37, 42);
        case 27:
            return randIntFromList(4, 26, 28, 37, 41);
        case 28:
            return randIntFromList(3, 27, 29, 38);
        case 29:
            return randIntFromList(3, 28, 30, 38);
        case 30:
            return randIntFromList(3, 29, 31, 38);
        case 31:
            return randIntFromList(4, 10, 30, 32, 33);
        case 32:
            return randIntFromList(3, 19, 31, 33);
        case 33:
            return randIntFromList(4, 31, 32, 34, 38);
        case 34:
            return randIntFromList(4, 19, 20, 33, 35);
        case 35:
            return randIntFromList(5, 21, 22, 23, 34, 36);
        case 36:
            return randIntFromList(4, 24, 25, 35, 37);
        case 37:
            return randIntFromList(4, 26, 27, 36, 38);
        case 38:
            return randIntFromList(5, 28, 29, 30, 33, 37);
        case 39:
            return randIntFromList(2, 40, 54);
        case 40:
            return randIntFromList(2, 39, 41);
        case 41:
            return randIntFromList(3, 27, 40, 42);
        case 42:
            return randIntFromList(3, 26, 41, 43);
        case 43:
            return randIntFromList(3, 25, 42, 44);
        case 44:
            return randIntFromList(3, 24, 43, 45);
        case 45:
            return randIntFromList(2, 44, 46);
        case 46:
            return randIntFromList(2, 45, 47);
        case 47:
            return randIntFromList(2, 46, 48);
        case 48:
            return randIntFromList(2, 47, 49);
        case 49:
            return randIntFromList(3, 48, 50, 60);
        case 50:
            return randIntFromList(2, 49, 51);
        case 51:
            return randIntFromList(2, 50, 52);
        case 52:
            return randIntFromList(2, 51, 53);
        case 53:
            return randIntFromList(2, 52, 54);
        case 54:
            return randIntFromList(2, 39, 53);
        case 55:
            return randIntFromList(2, 56, 70);
        case 56:
            return randIntFromList(2, 55, 57);
        case 57:
            return randIntFromList(2, 56, 58);
        case 58:
            return randIntFromList(2, 57, 59);
        case 59:
            return randIntFromList(2, 58, 60);
        case 60:
            return randIntFromList(3, 49, 59, 61);
        case 61:
            return randIntFromList(2, 60, 62);
        case 62:
            return randIntFromList(2, 61, 63);
        case 63:
            return randIntFromList(2, 62, 64);
        case 64:
            return randIntFromList(3, 63, 65, 76);
        case 65:
            return randIntFromList(3, 64, 66, 75);
        case 66:
            return randIntFromList(2, 65, 67);
        case 67:
            return randIntFromList(2, 66, 68);
        case 68:
            return randIntFromList(2, 67, 69);
        case 69:
            return randIntFromList(2, 68, 70);
        case 70:
            return randIntFromList(2, 69, 55);
        case 71:
            return randIntFromList(2, 72, 87);
        case 72:
            return randIntFromList(2, 71, 73);
        case 73:
            return randIntFromList(2, 72, 74);
        case 74:
            return randIntFromList(2, 73, 79);
        case 75:
            return randIntFromList(2, 65, 76);
        case 76:
            return randIntFromList(3, 64, 75, 77);
        case 77:
            return randIntFromList(2, 76, 78);
        case 78:
            return randIntFromList(2, 77, 79);
        case 79:
            return randIntFromList(3, 74, 78, 80);
        case 80:
            return randIntFromList(2, 79, 81);
        case 81:
            return randIntFromList(2, 80, 82);
        case 82:
            return randIntFromList(2, 81, 83);
        case 83:
            return randIntFromList(2, 82, 84);
        case 84:
            return randIntFromList(2, 83, 85);
        case 85:
            return randIntFromList(2, 84, 86);
        case 86:
            return randIntFromList(2, 85, 87);
        case 87:
            return randIntFromList(2, 86, 71);
        default:
            assert(0);
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

    int index = randUnif(1, 87);
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



