/**
 *  main.c - folly
 *
 *  This is the main module for the folly project. 
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include "game.h"
#include "ncwindow.h"


void printTitleAndWait(char* version);


int main() {

    // Print the title screen
    char* VERSION = "0.1";
    printTitleAndWait(VERSION);

    // Initialize and run the game inside an ncurses window
	WINDOW *window = startNCWindow();
    initGame(window);
    runGame();
    endNCWindow();

	return 0;
}

/**
 *  Prints the version number and 'FOLLY' in ASCII-art
 *  Then it waits for keyboard input
 */
void printTitleAndWait(char* version) {
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

