#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>

#include "game.h"
#include "ncwindow.h"

void showTitleScreen(char* version);

int main() {

    char* VERSION = "0.1";
    showTitleScreen(VERSION);

	WINDOW *window = startNCWindow();
    initGame(window);
    runGame();
    endNCWindow();

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

