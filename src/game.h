#ifndef GAME_H_
#define GAME_H_

static const int DELAY;

typedef struct Coordinates Coordinates;
struct Coordinates {
    int x;
    int y;
};

typedef struct GameState GameState;
struct GameState {
    int moveDir;
    Coordinates playerPosition;
    Coordinates maximumPosition;
};

void initGame(WINDOW* window);
void runGame();

#endif // GAME_H_
