#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "score.h"

typedef struct {
    int count;
    int countMax;
    Score* scores;
} Leaderboard;

Leaderboard* createLeaderboard(int count);

int getLeaderboardPosition(const Leaderboard* leaderboard, int score);

int updateLeaderboard(Leaderboard* leaderboard, Score score);

void destroyLeaderboard(Leaderboard* leaderboard);

#endif
