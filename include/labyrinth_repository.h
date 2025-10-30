#ifndef LABYRINTH_REPOSITORY_H
#define LABYRINTH_REPOSITORY_H

#include "labyrinth.h"
#include "leaderboard.h"

int getLabyrinthsNames(char** names, int namesLength, int stringLength);

Labyrinth* loadLabyrinth(const char* labyrinthName);

int saveLabyrinth(const char* labyrinthName, const Labyrinth* labyrinth);


// count or -1
Leaderboard* loadLeaderboard(const char* labyrinthName);

// 1 or 0
int saveLeaderboard(const char* labyrinthName, const Leaderboard* leaderboard);

#endif
