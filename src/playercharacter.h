/**
 *  playercharacter.h - folly
 *
 *  This module defines ...
 *
 */

#ifndef PLAYERCHARACTER_H_
#define PLAYERCHARACTER_H_

#include "ncwindow.h"

/**
 *  A tile in the game map
 */
typedef struct _PlayerCharacter {

    char* name;

    int x;
    int y;

    int healthPoints;
    int maxHealthPoints;

    int lightRadius;

    char* equipedWeapon;
    char* equipedShield;
} PlayerCharacter;

/**
 *  Initializes the player's character
 */
PlayerCharacter initPlayerCharacter();

/**
 *  Displays the player character on the tiled map
 */
void displayPlayerCharacter(PlayerCharacter* player);

void movePlayerCharacter(PlayerCharacter* player, int deltaX, int deltaY);


#endif // PLAYERCHARACTER_H_
