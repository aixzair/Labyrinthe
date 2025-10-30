#include "leaderboard.h"

#include <stdio.h>

Leaderboard* createLeaderboard(int count) {
    Leaderboard* leaderboard = malloc(sizeof(Leaderboard));
    
    leaderboard->count = 0;
    leaderboard->countMax = count;
    leaderboard->scores = malloc(sizeof(Score) * count);

    return leaderboard;
}

int getLeaderboardPosition(const Leaderboard* leaderboard, int score) {
    int position;
    for (position = 0; position < leaderboard->count; position++) {
        if (score > leaderboard->scores[position]) {
            break;
        }
    }

    if (position == leaderboard->countMax) {
        return -1;
    }

    return position;
}

int updateLeaderboard(Leaderboard* leaderboard, Score score) {
    int position = getLeaderboardPosition(leaderboard, score.score);
    if (position < 0) {
        return 0;
    }

    Score temp;
    for (; position < leaderboard->count; position++) {
        temp = leaderboard->scores[position];
        leaderboard->scores[position] = score;
        score = temp;
    }

    if (leaderboard->count < leaderboard->countMax) {
        leaderboard->scores[position] = score;
        leaderboard->count++;
    }
}

void destroyLeaderboard(Leaderboard* leaderboard) {
    leaderboard->count = -1;
    leaderboard->countMax = -1;
    free(leaderboard->scores);
    leaderboard->scores = NULL;
}
