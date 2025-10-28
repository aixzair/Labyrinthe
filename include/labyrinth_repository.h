#ifndef LABYRINTH_REPOSITORY_H
#define LABYRINTH_REPOSITORY_H

#include "labyrinth.h"

typedef struct {
    char* playerName;
    int score;
} Score;

int getLabyrinthsNames(char** names, int namesLength, int stringLength);

Labyrinth* loadLabyrinth(char* fileName);

int saveLabyrinth(const char* fileName, const Labyrinth* labyrinth);

// int loadScores(const char* fileName, Score* scores, int scoresLength);

// int saveScores(const char* fileName, Score* scores, int count);

#endif
