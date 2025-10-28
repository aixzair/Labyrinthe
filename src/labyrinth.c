#include "labyrinth.h"

int isValidSquare(const Labyrinth* labyrinth, int x, int y) {
    return labyrinth != NULL
        && (size_t) y < labyrinth->height
        && (size_t) x < labyrinth->width;
}

Square getSquare(const Labyrinth* labyrinth, int x, int y) {
    if (!isValidSquare(labyrinth, x, y)) {
        return SQU_NULL;
    }

    return labyrinth->squares[y][x];
}

int setSquare(const Labyrinth* labyrinth, int x, int y, Square square) {
    if (!isValidSquare(labyrinth, x, y)) {
        return 0;
    }

    labyrinth->squares[y][x] = square;

    return 1;
}

void destroyLabyrinth(Labyrinth* labyrinth) {
    free(labyrinth->name);
    for (size_t line = 0; line < labyrinth->height; line++) {
        free(labyrinth->squares[line]);
    }
    free(labyrinth->squares);

    labyrinth->name = NULL;
    labyrinth->height = 0;
    labyrinth->width = 0;
    labyrinth->squares = NULL;
}
