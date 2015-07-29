/**
 *  statusbar.c - folly
 *
 *  This module defines ...
 *
 */

#include <string.h>
#include "statusbar.h"
#include "playercharacter.h"


static int addStringToBar(char* str, int index, textColorPair color);

static void clearToBar(int start, int stop, textColorPair color);

/**
 *  Displays the ...
 */
void displayStatusBar(WINDOW* window, PlayerCharacter* player) {

    int maxY = 0;
    int maxX = 0;
    getmaxyx(window, maxY, maxX);

    int index = 0;
    index = addStringToBar("  Player1    ", index, BLACK_ON_WHITE);
    index = addStringToBar("HP: ", index, BLUE_ON_WHITE);
    char healthString[15];
    sprintf(healthString, "%d/%d    ", player->healthPoints, player->maxHealthPoints);
    index = addStringToBar(healthString, index, BLACK_ON_WHITE);
    index = addStringToBar("W: ", index, BLUE_ON_WHITE);
    char weaponString[30];
    sprintf(weaponString, "%s    ", player->equipedWeapon);
    index = addStringToBar(weaponString, index, BLACK_ON_WHITE);
    index = addStringToBar("S: ", index, BLUE_ON_WHITE);
    char shieldString[30];
    sprintf(shieldString, "%s", player->equipedShield);
    index = addStringToBar(shieldString, index, BLACK_ON_WHITE);

    clearToBar(index, maxX, BLACK_ON_WHITE);

}

static int addStringToBar(char* str, int index, textColorPair color) {
    int x = 0;
    char c = str[x];
    while (c != '\0') {
        printChar(c, index, 0, color);

        x += 1;
        c = str[x];
        index += 1;
    }
    return index;
}

static void clearToBar(int start, int stop, textColorPair color) {
    for (int i=start; i <= stop; i++) {
        printChar(' ', i, 0, color);
    }
}

