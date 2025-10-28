#ifndef MENU_H
#define MENU_H

#include "labyrinth.h"

typedef enum {
    ACT_CREATE,
    ACT_LOAD,
    ACT_PLAY,
    ACT_QUIT
} Action;

typedef struct {   
    Labyrinth* labyrinth;
} Menu;

#endif
