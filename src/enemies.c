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
#include "randfolly.h"


static int NUMBER_OF_ENEMIES = 20;

/**
 * Initializes a new enemy entity
 */
Enemy* initEnemy(Map* map) {

    Enemy* enemy = malloc(sizeof(Enemy));

    enemy->name = "an orc";

    enemy->displayChar = 'o';
    enemy->displayColor = GREEN_ON_BLACK;

    do {
        int x = randUnif(1, map->xDim - 1);
        int y = randUnif(1, map->yDim - 1);
        enemy->position = initMapCoordinate(x, y);
    } while(isLocationWall(map, enemy->position));

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
 * Displays an enemy on the game screen
 */
void displayEnemy(WINDOW* window, PlayerCharacter* player, Map* map, Enemy* enemy) {
    if (isVisible(map, enemy->position)) {
        printCharBoldPC(enemy->displayChar, enemy->position, window, player->position, enemy->displayColor);
    }
}

/**
 * Initializes a new boss-type enemy entity
 */
Enemy* initBoss(Map* map) {

    Enemy* boss = malloc(sizeof(Enemy));

    boss->name = "the Wraith";

    boss->displayChar = 'W';
    boss->displayColor = BLUE_ON_BLACK;

    do {
        int x = randUnif(1, map->xDim - 1);
        int y = randUnif(1, map->yDim - 1);
        boss->position = initMapCoordinate(x, y);
    } while(isLocationWall(map, boss->position));

    boss->next = NULL;
    boss->previous = NULL;

    return boss;
}

/**
 * Initializes collection of enemies
 */
AllEnemies* initAllEnemies(Map* map) {

    AllEnemies* allEnemies = malloc(sizeof(AllEnemies));

    allEnemies->head = NULL;
    allEnemies->tail = NULL;
    allEnemies->levelBoss = NULL;

    // Set boss
    allEnemies->levelBoss = initBoss(map);
    insertEnemy(allEnemies, allEnemies->levelBoss);

    // Set other enemies
    for (int i=0; i < NUMBER_OF_ENEMIES; i++) {
        Enemy* newEnemy = initEnemy(map);
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

    Enemy* current = allEnemies->head;

    while (current != NULL) {
        displayEnemy(window, player, map, current);
        current = current->next;
    }
}

/**
 * Inserts an enemy into the collection of all enemies
 */
void insertEnemy(AllEnemies* allEnemies, Enemy* enemy) {
    if (allEnemies->tail == NULL) {
        allEnemies->head = enemy; 
        allEnemies->tail = enemy;
        enemy->next = NULL;
        enemy->previous = NULL;
    }

    allEnemies->tail->next = enemy;
    enemy->previous = allEnemies->tail;
    enemy->next = NULL;
    allEnemies->tail = enemy;
}

/**
 * Removes an enemy from the collection of all enemies
 */
void removeEnemy(AllEnemies* allEnemies, Enemy* enemy) {

}

