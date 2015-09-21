/**
 *  map.c - folly
 *
 *  This module defines the grid of ASCII tiles used as the main gameplay map.
 *
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bresenhamline.h"
#include "debugfolly.h"
#include "map.h"
#include "maptile.h"
#include "randfolly.h"
#include "enemies.h"


void static traceLineOfSight(Map* map, MapCoordinate playerPos, MapCoordinate endPos);

/**
 * Initializes the game map
 */
Map* initMap() {
    Map* map = malloc(sizeof(Map));
    assert(map != NULL);

    char fileName[32];
    int randomInt = randUnif(0, 3);
    sprintf(fileName, "data/maps/small_maze_%d.txt", randomInt);

    FILE* mapFile;
    mapFile = fopen(fileName, "r");

    int xDim = 0;
    int yDim = 0;
    char buf[1000];
    while(fgets(buf, 1000, mapFile) != NULL) {
        yDim++;
    }
    fclose(mapFile);

    // Allocate map tiles to fit the y-dimension
    map->tiles = (MapTile**)malloc(sizeof(MapTile*) * yDim);
    if (! map->tiles) {
        perror("Error allocating memory. See initMap() in map.c");
        abort();
    }

    mapFile = fopen(fileName, "r");
    char* line = fgets(buf, 1000, mapFile);
    int y = 0;
    while (line != NULL) {

        // Allocate map tiles to fit the x-dimension of the current row
        xDim = strlen(line);
        int i = 0;
        for (i=0; i < xDim; i++) {
            if (line[i] != '#' && line[i] != ' ') {
                break;
            }
        }
        xDim = i;

        map->tiles[y] = (MapTile*)malloc(sizeof(MapTile) * xDim);
        if (! map->tiles[y]) {
            perror("Error allocating memory. See initMap() in map.c");
            abort();
        }

        // Read the current row and initialize map tile to match
        int x = 0;
        char c = line[x];
        while (c == '#' || c == ' ') {
            if (c == '#') {
                // Add wall tile (#)
                map->tiles[y][x] = *initMapTile(x, y, 1);
            } else if (c == ' ') {
                // Add non-wall tile (.)
                map->tiles[y][x] = *initMapTile(x, y, 0);
            } else {
                break;
            }

            x++;
            c = line[x];
        }

        y++;
        line = fgets(buf, 1000, mapFile);
    }
    fclose(mapFile);

    map->yDim = yDim;
    map->xDim = xDim;

    return map;
}

/**
 * Frees dynamically allocated memory used for map tiles
 */
void deleteMap(Map** mapRef) {
    Map* map = *mapRef;
    for (int x=0; x < map->xDim; x++) {
        for (int y=0; y < map->yDim; y++) {
            //deleteMapTile(&(map->tiles[y][x]));
        }
    }

    free(*mapRef);
    *mapRef = NULL;
}

/**
 * Displays the map in an ncurses window
 */
void displayMap(const WINDOW* window, const Map* map, MapCoordinate playerPosition) {

    for (int y=0; y < map->yDim; y++) {
        for (int x=0; x < map->xDim; x++) {
            displayMapTile(window, &map->tiles[y][x], playerPosition);
        }
    }

    displayDebugStack(window);
}

/**
 * Updates the visibility status of map tiles based on the player's position and the radius of illumination around that position
 */
void updateVisibility(Map* map, MapCoordinate playerPosition, int lightRadius) {

    int playerX = playerPosition.x;
    int playerY = playerPosition.y;

    int xMinBox = playerX-lightRadius;
    int xMaxBox = playerX+lightRadius;
    int yMinBox = playerY-lightRadius;
    int yMaxBox = playerY+lightRadius;

    if (xMinBox < 0) {
        xMinBox = 0;
    } else if (xMinBox > map->xDim) {
        xMinBox = map->xDim;
    }

    if (xMaxBox < 0) {
        xMaxBox = 0;
    } else if (xMaxBox > map->xDim) {
        xMaxBox = map->xDim;
    }

    if (yMinBox < 0) {
        yMinBox = 0;
    } else if (yMinBox > map->yDim) {
        yMinBox = map->yDim;
    }

    if (yMaxBox < 0) {
        yMaxBox = 0;
    } else if (yMaxBox > map->yDim) {
        yMaxBox = map->yDim;
    }

    for (int i=0; i < map->yDim; i++) {
        for (int j=0; j < map->xDim; j++) {
            if (i < yMinBox || i > yMaxBox || j < xMinBox || j > xMaxBox) {
                map->tiles[i][j].visible = 0;
            } else {
                float h = (float)(i - playerY);
                float w = (float)(j - playerX);
                float dist = sqrt(w*w + h*h);
                if (dist < (float)lightRadius) {
                    map->tiles[i][j].visible = 1;
                    //map->tiles[i][j].explored = 1;
                } else {
                    map->tiles[i][j].visible = 0;
                }
            }
        }
    }

    for (int i = xMinBox + 1; i < xMaxBox; i++) {
        MapCoordinate topEdge = initMapCoordinate(i, yMaxBox);
        traceLineOfSight(map, playerPosition, topEdge);

        MapCoordinate bottomEdge = initMapCoordinate(i, yMinBox);
        traceLineOfSight(map, playerPosition, bottomEdge);
    }

    for (int j = yMinBox; j <= yMaxBox; j++) {
        MapCoordinate rightEdge = initMapCoordinate(xMaxBox, j);
        traceLineOfSight(map, playerPosition, rightEdge);

        MapCoordinate leftEdge = initMapCoordinate(xMinBox, j);
        traceLineOfSight(map, playerPosition, leftEdge);
    }


    for (int y = yMinBox; y < yMaxBox; y++) {
        for (int x = xMinBox; x < xMaxBox; x++) {
            if (map->tiles[y][x].visible == 1) {
                map->tiles[y][x].explored = 1;
            }
        }
    }
}

/**
 * Further refines the visibility status of tiles based on line-of-sight blocked by walls
 */
void static traceLineOfSight(Map* map, MapCoordinate playerPos, MapCoordinate endPos) {

    BresenhamLine* trace = initBresenhamLine(playerPos, endPos);

    /*BresenhamLine* current = trace;
    int hitWall = 0;

    while (current != NULL) {

        //if (hitWall) {
            setVisibility(map, current->location, 0);
        //}

        if (isLocationWall(map, current->location)) {
            hitWall = 1;
        }

        current = current->next;
    }*/

    deleteBresenhamLine(&trace);
}

/**
 * Returns 1 if a given location on the map can be traversed by the player (i.e. no obstacles like walls or enemies). Returns 0 otherwise.
 */
int isTraversable(const Map* map, MapCoordinate location) {
    int x = location.x;
    int y = location.y;
    if (!(map->tiles[y][x].isWall) && map->tiles[y][x].enemy == NULL) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * Sets the enemy at a given location
 */
void setEnemy(Map* map, Enemy* enemy, MapCoordinate location) {
    int x = location.x;
    int y = location.y;
    map->tiles[y][x].enemy = enemy;
}

/**
 * Sets the visibility status of the maptile at a given location.
 */
void setVisibility(Map* map, MapCoordinate location, int visibility) {
    int x = location.x;
    int y = location.y;
    map->tiles[y][x].visible = 1;
}

/**
 * Returns one if the position on the map is visible to the player
 */
int isVisible(const Map* map, MapCoordinate position) {
    int x = position.x;
    int y = position.y;
    return map->tiles[y][x].visible;
}

