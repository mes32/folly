/**
 *  enemies.c - folly
 *
 *  This module defines enemies that the player character encounters and fights in the game.
 *
 */

#include <stdlib.h>
#include <string.h>

#include "enemies.h"
#include "mapcoordinate.h"
#include "playercharacter.h"
#include "map.h"


static int NUMBER_OF_ENEMIES = 0;

/**
 * Initializes a new enemy entity
 */
Enemy* initEnemy() {

    Enemy* enemy = malloc(sizeof(Enemy));

    enemy->name = "an orc";

    enemy->displayChar = 'o';
    enemy->displayColor = GREEN_ON_BLACK;
    enemy->position = initMapCoordinate(22, 22);

    enemy->next = NULL;
    enemy->previous = NULL;

    return enemy;
}

/**
 * Deletes enemy and frees alocated memory
 */
void deleteEnemy(Enemy** enemy) {

}

/**
 * Initializes a new boss-type enemy entity
 */
Enemy* initBoss() {

    Enemy* boss = malloc(sizeof(Enemy));

    boss->name = "the Wraith";

    boss->displayChar = 'W';
    boss->displayColor = BLUE_ON_BLACK;
    boss->position = initMapCoordinate(5, 5);

    boss->next = NULL;
    boss->previous = NULL;

    return boss;
}

/**
 * Initializes collection of enemies
 */
AllEnemies* initAllEnemies() {

    AllEnemies* allEnemies = malloc(sizeof(AllEnemies));

    allEnemies->head = NULL;
    allEnemies->tail = NULL;
    allEnemies->levelBoss = NULL;

    // Set boss
    allEnemies->levelBoss = initBoss();
    insertEnemy(allEnemies, allEnemies->levelBoss);

    // Set other enemies
    for (int i=0; i < NUMBER_OF_ENEMIES; i++) {
        Enemy* newEnemy = initEnemy();
        insertEnemy(allEnemies, newEnemy);
    }

    return allEnemies;
}

/**
 * Deletes all enemies and frees alocated memory
 */
void deleteAllEnemies(AllEnemies** allEnemiesRef) {

}

/**
 *  Displays all visible enemies relative to the player's position on the ncurses window
 */
void displayAllEnemies(WINDOW* window, PlayerCharacter* player, AllEnemies* allEnemies, Map* map) {

    Enemy* boss = allEnemies->levelBoss;

    if (isVisible(map, boss->position)) {
        printCharBoldPC(boss->displayChar, boss->position, window, player->position, boss->displayColor);
    }
}

/**
 * Inserts an enemy into the collection of all enemies
 */
void insertEnemy(AllEnemies* allEnemies, Enemy* enemy) {

}

/**
 * Removes an enemy from the collection of all enemies
 */
void removeEnemy(AllEnemies* allEnemies, Enemy* enemy) {

}

