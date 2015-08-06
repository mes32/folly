/**
 *  playercharacter.c - folly
 *
 *  This module defines ...
 *
 */

#include "mapcoordinate.h"
#include "playercharacter.h"


/**
 *  Initializes a map tile
 */
PlayerCharacter initPlayerCharacter() {
    PlayerCharacter player;

    player.name = "Player1";
    player.position = initMapCoordinate(1, 2);
    player.healthPoints = 20;
    player.maxHealthPoints = 20;
    player.lightRadius = 5;
    player.equipedWeapon = "Short Sword";
    player.equipedShield = "Small Round Shield";

    return player;
}

/**
 *  Displays the map tile in an ncurses window at the given coordinates
 */
void displayPlayerCharacter(WINDOW* window, PlayerCharacter* player) {

    MapCoordinate playerPosition = player->position;

    printCharBoldPC('@', playerPosition, window, playerPosition, WHITE_ON_BLACK);
}

void movePlayerCharacter(PlayerCharacter* player, int deltaX, int deltaY) {
    movePosition(&player->position, deltaX, deltaY);
}

