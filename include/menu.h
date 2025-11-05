#ifndef MENU_H
#define MENU_H

#include "labyrinth.h"

typedef enum {
    ACT_CREATE,
    ACT_LOAD,
    ACT_PLAY,
    ACT_SCORE,
    ACT_QUIT
} Action;

typedef struct {   
    Labyrinth* labyrinth;
} Menu;

Menu* createMenu();

void destroyMenu(Menu* menu);

void createLabyrinthAction(Menu* menu);

void loadLabyrinthAction(Menu* menu);

void playGameAction(Menu* menu);

void showScoresActoin(Menu* menu);

#endif
