#ifndef MONSTERS
#define MONSTERS

#include <stdlib.h>

#include "labyrinth.h"
#include "position.h"

typedef struct Monster {
    Position position;
    void (*move)(struct Monster* self);
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

    int monstersHits;
    int penalityCount;
} Monsters;


void addMonsters(Labyrinth* labyrinth);

Monsters* getMonsters(const Labyrinth* labyrinth);

void moveMonsters(Labyrinth* labyrinth, Monsters* monsters);

void destroyMonsters(Monsters* monsters);

#endif
