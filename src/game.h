#ifndef GAME_H_
#define GAME_H_

#define WIDTH 100
#define HEIGHT 100
#define DELAY 30000

typedef struct coordinates coordinates;
struct coordinates {
    int x;
    int y;
};

typedef struct gameState gameState;
struct gameState {
    int moveDir;
    coordinates playerPosition;
    coordinates maximumPosition;
};

void initColors();
void displayHelpScreen(WINDOW *window);
void displayDeathScreen(WINDOW *window);
void updateGameState(int input, gameState *game);
void displayGameScreen(WINDOW *window, gameState *game);

#endif // GAME_H_
