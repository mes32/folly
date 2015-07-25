#ifndef GAME_H_
#define GAME_H_

static const int DELAY;

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
void displayGameScreen(WINDOW *window, gameState *game);

void updateGameState(int input, gameState *game);

void runGame(WINDOW* window);

#endif // GAME_H_
