#include "labyrinth.h"

// Implémentations --------------------------------------------------------------------------------

int isValidSquare(const Labyrinth* labyrinth, int line, int col) {
    return labyrinth != NULL
        && (size_t) line < labyrinth->height
        && (size_t) col < labyrinth->width;
}

Square getSquare(const Labyrinth* labyrinth, int line, int col) {
    if (!isValidSquare(labyrinth, line, col)) {
        return SQU_NULL;
    }

    return labyrinth->squares[line][col];
}

int setSquare(const Labyrinth* labyrinth, int line, int col, Square square) {
    if (!isValidSquare(labyrinth, line, col)) {
        return 0;
    }

    labyrinth->squares[line][col] = square;

    return 1;
}

void destroyLabyrinth(Labyrinth* labyrinth) {
    if (labyrinth == NULL) {
        return;
    }

    free(labyrinth->name);
    for (size_t line = 0; line < labyrinth->height; line++) {
        free(labyrinth->squares[line]);
    }
    free(labyrinth->squares);

    labyrinth->name = NULL;
    labyrinth->height = 0;
    labyrinth->width = 0;
    labyrinth->squares = NULL;
    free(labyrinth);
}
