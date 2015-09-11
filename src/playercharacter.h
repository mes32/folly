/**
 *  playercharacter.h - folly
 *
 *  This module defines the player's character
 *
 */

#ifndef PLAYERCHARACTER_H_
#define PLAYERCHARACTER_H_

#include "mapcoordinate.h"
#include "ncwindow.h"

/**
 * The player's character
 */
typedef struct _PlayerCharacter {
    char* name;
    MapCoordinate position;
    int healthPoints;
    int maxHealthPoints;
    int lightRadius;
    char* equipedWeapon;
    char* equipedShield;
} PlayerCharacter;

/**
 * Initialize the player's character
 */
PlayerCharacter* initPlayerCharacter();

/**
 * Displays the player character on the tiled map
 */
void displayPlayerCharacter(WINDOW* window, PlayerCharacter* player);

/**
 * Change the player character's location
 */
void movePlayerCharacter(PlayerCharacter* player, int deltaX, int deltaY);


#endif // PLAYERCHARACTER_H_
