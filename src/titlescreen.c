/**
 *  titlescreen.c - folly
 *
 *  This module shows an ncurses based title screen
 *
 */

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#include "ncwindow.h"
#include "titlescreen.h"

static void printFolly(int maxX);

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

    while (1) {
        mvprintw(14, (maxX - 44)/2 + 23, "   ");
        move(0, 0);
        refresh();
        usleep(400000);
        mvprintw(14, (maxX - 44)/2 + 23, ".  ");
        move(0, 0);
        refresh();
        usleep(300000);
        mvprintw(14, (maxX - 44)/2 + 23, ".. ");
        move(0, 0);
        refresh();
        usleep(200000);
        mvprintw(14, (maxX - 44)/2 + 23, "...");
        move(0, 0);
        refresh();
        usleep(600000);
    }
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



