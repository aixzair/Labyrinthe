#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <stdlib.h>

typedef enum {
    SQU_WALL,
    SQU_PLAYER,
    SQU_CORRIDOR,
    SQU_DOOR,
    SQU_END,
    SQU_COIN,
    SQU_TRAP,
    SQU_KEY,
    SQU_NULL,
    SQU_OGRE,
    SQU_SPECTRUM,
    SQU_SPECTRUM_IN_WALL
} Square;

typedef struct {
    char* name;
    size_t height;
    size_t width;
    Square** squares;
} Labyrinth;

int isValidSquare(const Labyrinth* labyrinth, int line, int col);

Square getSquare(const Labyrinth* labyrinth, int line, int col);

int setSquare(const Labyrinth* labyrinth, int line, int col, Square square);

void destroyLabyrinth(Labyrinth* labyrinth);

#endif
