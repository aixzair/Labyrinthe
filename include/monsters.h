#ifndef MONSTERS
#define MONSTERS

#include <stdlib.h>

#include "labyrinth.h"
#include "position.h"

typedef struct Monster {
    Position position;
    void (*move)(struct Monster* self, Labyrinth* labyrinth, int penality);
    void (*destroy)(struct Monster* self);
} Monster;

typedef struct {
    Monster base;
    Position coin;
    int distance;
} Ogre;

typedef struct {
    Monster base;
    int speed;
} Spectrum;

typedef struct {
    size_t count;
    Monster** monsters;
    int penalityCount;
} Monsters;


void addMonsters(Labyrinth* labyrinth);

Monsters* getMonsters(const Labyrinth* labyrinth);

int isMonster(const Labyrinth* labyrinth, Position position);

void killMonster(Monsters* monsters, Position position);

void moveMonsters(Labyrinth* labyrinth, Monsters* monsters);

void destroyMonsters(Monsters* monsters);

#endif
