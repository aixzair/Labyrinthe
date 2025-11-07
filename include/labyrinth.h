#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <stdlib.h>

typedef enum {
    SQU_CORRIDOR,
    SQU_WALL,
    SQU_COIN,
    SQU_TRAP,
    SQU_KEY,
    SQU_DOOR,
    SQU_END,
    SQU_PLAYER,
    SQU_OGRE,
    SQU_OGRE_IN_COIN,
    SQU_OGRE_IN_TRAP,
    SQU_OGRE_IN_KEY,
    SQU_SPECTRUM,
    SQU_SPECTRUM_IN_WALL,
    SQU_SPECTRUM_IN_COIN,
    SQU_SPECTRUM_IN_TRAP,
    SQU_SPECTRUM_IN_KEY,
    SQU_NULL,
} Square;

typedef struct {
    char* name;
    size_t height;
    size_t width;
    Square** squares;
    int monsters;
} Labyrinth;

int isValidSquare(const Labyrinth* labyrinth, int line, int col);

Square getSquare(const Labyrinth* labyrinth, int line, int col);

int setSquare(const Labyrinth* labyrinth, int line, int col, Square square);

void destroyLabyrinth(Labyrinth* labyrinth);

#endif
