/**
 *  main.c - folly
 *
 *  This is the main module for the folly project. 
 *
 */

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "debugfolly.h"
#include "game.h"
#include "ncwindow.h"


void printTitleAndWait(char* version, unsigned int randomSeed);


int main(int argc, char *argv[]) {

    // Initialize debug messages once for the program
    initDebugStack();

    // Setup random seed
    unsigned int randomSeed = 0;
    if (argc > 1) {
        randomSeed = (unsigned int)atoi(argv[1]);
    } else {
        randomSeed = (unsigned int)time(NULL);
    }

    // Print the title screen
    char* VERSION = "0.1";
    printTitleAndWait(VERSION, randomSeed);

    // Initialize and run the game inside an ncurses window
	WINDOW *window = startNCWindow();
    initGame(window, randomSeed);
    runGame();
    endNCWindow();

	return 0;
}

/**
 *  Prints the version number and 'FOLLY' in ASCII-art
 *  Then it waits for keyboard input
 */
void printTitleAndWait(char* version, unsigned int randomSeed) {
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
    printf("RANDOM SEED: %u\n", randomSeed);
    printf("\n");
    printf("Press enter to continue.\n");

    getchar();
}

