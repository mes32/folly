/**
 *  main.c - folly
 *
 *  This is the main module for the folly project. 
 *
 */

#include <ncurses.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "debugfolly.h"
#include "game.h"
#include "ncwindow.h"
#include "titlescreen.h"


static void* threadFunc(void *window);
void printTitleAndWait(char* version, unsigned int randomSeed);


int main(int argc, char *argv[]) {

    // Initialize debug messages once for the entire program
    initDebugStack();

    // Setup random seed
    unsigned int randomSeed = 0;
    if (argc > 1) {
        randomSeed = (unsigned int)atoi(argv[1]);
    } else {
        randomSeed = (unsigned int)time(NULL);
    }

    // Print the title screen and random seed used
    char* VERSION = "0.1";
    printTitleAndWait(VERSION, randomSeed);

    // Start pthread
	WINDOW *window = startNCWindow();
    pthread_t pth;
	pthread_create(&pth, NULL, threadFunc, window);

    // Start ncurses window and wait for key press before killing pthread
    wgetch(window);
    termTitleScreenThreads();
    pthread_cancel(pth);

    // Initialize and run the game
    initGame(window, randomSeed);
    runGame();
    endNCWindow();

	return 0;
}

/**
 *  Prints the version number and 'FOLLY' in ASCII-art
 */
void printTitleAndWait(char* version, unsigned int randomSeed) {
    printf("\n");
    printf("Started Folly v%s\n", version);
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
    printf("RANDOM SEED: %u\n", randomSeed);
    printf("\n");

    usleep(200000);
}

static void* threadFunc(void *window) {
    displayTitleScreen(window);
    return NULL;
}

