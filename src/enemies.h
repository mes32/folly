/**
 *  enemies.h - folly
 *
 *  This module defines enemies that the player character encounters and fights in the game.
 *
 */

#ifndef ENEMIES_H_
#define ENEMIES_H_

//#include "mapcoordinate.h"
#include "ncwindow.h"
#include "playercharacter.h"
#include "map.h"


/*typedef enum {
    IMMOBILE,
    WAIT,
    WANDER
} MovementStyle;*/

/*typedef enum {
    STATIONARY,
    EVASIVE,
    RELENTLESS,
    HIT_AND_RUN,
    CHAOTIC,
    ENCIRCLE,
    KITE
} AttackStyle;*/

typedef struct _Enemy Enemy;
struct _Enemy {
    char* name;
    char* description;

    char displayChar;
    textColorPair displayColor;
    MapCoordinate position;

    int healthPoints;
    int maxHealthPoints;

    int lightRadius;

    Enemy* next;
    Enemy* previous;
};

typedef struct _AllEnemies {
    Enemy* head;
    Enemy* tail;
    Enemy* levelBoss;
} AllEnemies;

/**
 * Initializes a new enemy entity
 */
Enemy* initEnemy(Map* map, MapCoordinate playerPosition);

/**
 * Deletes enemy and frees alocated memory
 */
void deleteEnemy(Enemy** enemyRef);

/**
 * Displays an enemy on the game screen
 */
void displayEnemy(const WINDOW* window, const PlayerCharacter* player, const Map* map, const Enemy* enemy);

/**
 * Initializes a new boss-type enemy entity
 */
Enemy* initBoss(Map* map, MapCoordinate playerPosition);

/**
 * Initializes collection of enemies
 */
AllEnemies* initAllEnemies(Map* map, MapCoordinate playerPosition);

/**
 * Deletes all enemies and frees alocated memory
 */
void deleteAllEnemies(AllEnemies** allEnemiesRef);

/**
 *  Displays all visible enemies relative to the player's position on the ncurses window
 */
void displayAllEnemies(const WINDOW* window, const PlayerCharacter* player, const AllEnemies* allEnemies, const Map* map);

/**
 * Inserts an enemy into the collection of all enemies
 */
void insertEnemy(AllEnemies* allEnemies, Enemy* enemy);

/**
 * Removes an enemy from the collection of all enemies
 */
void removeEnemy(AllEnemies* allEnemies, Enemy* enemy);


#endif // ENEMIES_H_
