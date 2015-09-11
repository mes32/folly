/**
 *  playercharacter.c - folly
 *
 *  This module defines the player's character
 *
 */

#include <assert.h>

#include "mapcoordinate.h"
#include "playercharacter.h"


/**
 * Initialize the player's character
 */
PlayerCharacter* initPlayerCharacter() {
    PlayerCharacter* player = malloc(sizeof(PlayerCharacter));
    assert(player != NULL);

    player->name = "Player1";
    player->position = initMapCoordinate(1, 2);
    player->healthPoints = 20;
    player->maxHealthPoints = 20;
    player->lightRadius = 5;
    player->equipedWeapon = "Short Sword";
    player->equipedShield = "Small Round Shield";

    return player;
}

/**
 * Displays the player character on the tiled map
 */
void displayPlayerCharacter(WINDOW* window, PlayerCharacter* player) {

    MapCoordinate playerPosition = player->position;

    printCharBoldPC('@', playerPosition, window, playerPosition, WHITE_ON_BLACK);
}

/**
 * Change the player character's location
 */
void movePlayerCharacter(PlayerCharacter* player, int deltaX, int deltaY) {
    movePosition(&player->position, deltaX, deltaY);
}

