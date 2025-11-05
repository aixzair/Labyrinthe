#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "game.h"
#include "leaderboard.h"
#include "menu.h"

Action displayMenu(const Menu* menu);

void displayLabyrinthGenerationForm(size_t* height, size_t* width, char* name, size_t nameLength);

int displayLabyrintsAvailable(char** names, int count);

Direction displayGame(const Game* game);

void displayGameOver(const Game* game, const Leaderboard* leaderboard, char playerName[PLAYER_NAME_LENGTH]);

void displayLeaderboard(const char* labyrinthName, const Leaderboard* leaderboard);

#endif
