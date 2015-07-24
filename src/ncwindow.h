#ifndef NCWINDOW_H_
#define NCWINDOW_H_

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
    WINDOW* menu_win;
    int moveDir;
    coordinates playerPosition;
    coordinates maximumPosition;
};

int dummyWindowFunction();

void showHelpScreen(WINDOW *menu_win);
void showGameOverScreen(WINDOW *menu_win);

void updateGameState(int input, gameState *game);

WINDOW* openGameWindow();
void refreshGameWindow(gameState *game);
void closeGameWindow();

#endif // NCWINDOW_H_
