/**
 *  map.c - folly
 *
 *  This module defines the grid of ASCII tiles used as the main gameplay map.
 *
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "maptile.h"
#include "playercharacter.h"


/**
 *  Initializes the game map
 */
Map initMap(int xDim, int yDim) {
    Map map;
    map.xDim = xDim;
    map.yDim = yDim;

    map.tiles = (MapTile**)malloc(sizeof(MapTile*) * xDim);
    if (! map.tiles) {
        perror("Error allocating memory. See initMap() in map.c");
        abort();
    }

    for (int i=0; i < xDim; i++) {
        map.tiles[i] = (MapTile*)malloc(sizeof(MapTile) * yDim);
        if (! map.tiles[i]) {
            perror("Error allocating memory. See initMap() in map.c");
            abort();
        }
    }

    for (int x=0; x < xDim; x++) {
        for (int y=0; y < yDim; y++) {
            if (x == 0 || y == 0 || x == xDim-1 || y == yDim-1) {
                // Add wall tile
                map.tiles[x][y] = initMapTile(1);
            } else {
                // Add non-wall tile
                map.tiles[x][y] = initMapTile(0);
            }
        }
    }

    return map;
}

/**
 *  Frees dynamically allocated memory used for map tiles
 */
void deleteMap(Map* map) {
    for (int x = map->xDim - 1; x >= 0; x--) {
        free(map->tiles[x]);
    }
    free(map->tiles);
}

/**
 *  Displays the map in an ncurses window
 */
void displayMap(WINDOW* window, Map* map, PlayerCharacter* player) {
    for (int x=0; x < map->xDim; x++) {
        for (int y=0; y < map->yDim; y++) {
            displayMapTile(window, &map->tiles[x][y], x, y, player);
        }
    }
}

void updateVisibility(Map* map, int playerX, int playerY, int lightRadius) {

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

    for (int i=0; i < map->xDim; i++) {
        for (int j=0; j < map->yDim; j++) {
            if (i < xMinBox || i > xMaxBox || j < yMinBox || j > yMaxBox) {
                map->tiles[i][j].visible = 0;
            } else {
                float h = (float)(j - playerY);
                float w = (float)(i - playerX);
                float dist = sqrt(w*w + h*h);
                if (dist < (float)lightRadius) {
                    map->tiles[i][j].visible = 1;
                    map->tiles[i][j].explored = 1;
                } else {
                    map->tiles[i][j].visible = 0;
                }
            }
        }
    }

    // Line-of-sight trace to bottome edge of light radius block (See Bresenham's Line Algorithm)
    /*for (int i = xMinBox; i < xMaxBox; i++) {
        int j = yMinBox;
        int hitWall = 0;

        int x0 = playerX;
        int y0 = playerY;
        int x1 = i;
        int y1 = yMaxBox;

        float deltaX = (float)x1 - (float)x0;
        float deltaY = (float)y1 - (float)y0;
        if (deltaX == 0)
            continue;
        float err = 0;
        float deltaErr = abs(deltaY/deltaX);

        int y = y0;
        for (int x=x0; x < x1; x++) {
            if (map->tiles[x][y].isWall) {
                hitWall = 1;
            }
            if (hitWall) {
                map->tiles[i][j].visible = 0;
            }
            err += deltaErr;
            while (err >= 0.5) {
                if (map->tiles[x][y].isWall) {
                    hitWall = 1;
                }
                if (hitWall) {
                    map->tiles[i][j].visible = 0;
                }
                if ((y1 - y0) < 0) {
                    y -= 1;
                } else if ((y1 - y0) > 0) {
                    y += 1;
                }
                err -= 1.0;
            }
        }

    }

    for (int i = xMinBox; i < xMaxBox; i++) {
        for (int j = yMinBox; j < yMaxBox; j++) {
            if (map->tiles[i][j].visible == 1) {
                map->tiles[i][j].explored = 1;
            }
        }
    }*/
}

