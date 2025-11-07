#ifndef GAME_H
#define GAME_H

#include "labyrinth.h"
#include "position.h"
#include "monsters.h"

typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_RIGHT,
    DIR_LEFT
} Direction;

typedef struct {
    int score;
    int gameOver;
    Position playerPosition;
    Labyrinth* labyrinth;
    Monsters* monsters;
} Game;

Game* startGame(Labyrinth* labyrinth);

int move(Game* game, Direction direction);

int isGameOver(Game* game);

void endGame(Game* game);

#endif
