/**
 *  playercharacter.c - folly
 *
 *  This module defines ...
 *
 */

#include "playercharacter.h"


/**
 *  Initializes a map tile
 */
PlayerCharacter initPlayerCharacter() {
    PlayerCharacter player;

    player.x = 1;
    player.y = 1;
    player.healthPoints = 20;
    player.maxHealthPoints = 20;

    return player;
}

/**
 *  Displays the map tile in an ncurses window at the given coordinates
 */
void displayPlayerCharacter(PlayerCharacter* player) {
    attron(COLOR_PAIR(WHITE_ON_BLACK));
    attron(A_BOLD);
    mvprintw(player->y, player->x, "@");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(WHITE_ON_BLACK));
}

void movePlayerCharacter(PlayerCharacter* player, int deltaX, int deltaY) {
    player->x += deltaX;
    player->y += deltaY;
}

/**
 *  Displays the map tile in an ncurses window at the given coordinates
 */
//static void displayUnexplored(int x, int y) {
//    int k = 0;
//}
