#include "monsters.h"

#include <stdlib.h>

static int randomInt(int min, int max);

static Spectrum* createSpectrum(int line, int col);

static void destroySpectrum(Monster* monster);

static Ogre* createOgre(int line, int col, const Labyrinth* labyrinth);

static void destroyOgre(Monster* monster);


static int randomInt(int min, int max) {
    int range = max - min + 1;

    return (rand() % range) + min; 
}

static Spectrum* createSpectrum(int line, int col) {
    Spectrum* spectrum = malloc(sizeof(Spectrum));

    spectrum->base.move = NULL; // TODO
    spectrum->base.destroy = destroySpectrum;
    spectrum->base.position.y = line;
    spectrum->base.position.x = col;

    spectrum->speed = 1;

    return spectrum;
}

static void destroySpectrum(Monster* monster) {
    Spectrum* spectrum = (Spectrum*) monster;
    
    spectrum->base.move = NULL;
    free(spectrum);
    spectrum = NULL;
}

static Ogre* createOgre(int line, int col, const Labyrinth* labyrinth) {
    Ogre* ogre = malloc(sizeof(Ogre));

    ogre->base.move = NULL; // TODO
    ogre->base.destroy = destroyOgre;
    ogre->base.position.y = line;
    ogre->base.position.x = col;

    ogre->distance = 3;

    int success = 0;
    while (!success) {
        size_t coinLine = randomInt(1, labyrinth->height - 2);
        size_t coinCol = randomInt(1, labyrinth->width - 2);

        if (getSquare(labyrinth, coinLine, col) != SQU_COIN) {
            continue;
        }

        ogre->coin.y = coinLine;
        ogre->coin.x = coinCol;

        success = 1;
    }

    return ogre;
}

static void destroyOgre(Monster* monster) {
    Ogre* ogre = (Ogre*) monster;

    ogre->base.move = NULL;
    free(ogre);
    ogre = NULL;
}


void addMonsters(Labyrinth* labyrinth) {
    srand(time(NULL));

    // Enlève des murs
    size_t wallCount = (labyrinth->height - 2) * (labyrinth->width - 2) * 0.05;

    for (size_t i = 0; i < wallCount; i++) {
        int success = 0;
        do {
            int line = randomInt(1, labyrinth->height - 2);
            int col = randomInt(1, labyrinth->width - 2);

            if (getSquare(labyrinth, line, col) != SQU_WALL) {
                continue;
            }

            success = setSquare(labyrinth, line, col, SQU_CORRIDOR);
        } while (!success);
    }

    // Ajoute les ogres
    size_t ogreCount = (labyrinth->height - 2) * (labyrinth->width - 2) * 0.05;

    for (size_t i = 0; i < ogreCount; i++) {
        int success = 0;
        do {
            int line = randomInt(1, labyrinth->height - 2);
            int col = randomInt(1, labyrinth->width - 2);

            if (getSquare(labyrinth, line, col) != SQU_CORRIDOR) {
                continue;
            }

            success = setSquare(labyrinth, line, col, SQU_OGRE);
        } while (!success);
    }

    // Ajoute les spectres
    size_t spectrumCount = (labyrinth->height - 2) * (labyrinth->width - 2) * 0.05;

    for (size_t i = 0; i < spectrumCount; i++) {
        int success = 0;
        do {
            int line = randomInt(1, labyrinth->height - 2);
            int col = randomInt(1, labyrinth->width - 2);

            switch (getSquare(labyrinth, line, col)) {
                case SQU_CORRIDOR:
                    success = setSquare(labyrinth, line, col, SQU_SPECTRUM);
                    break;
                case SQU_WALL:
                    success = setSquare(labyrinth, line, col, SQU_SPECTRUM_IN_WALL);
                    break;
                default:
                    continue;
            }            
        } while (!success);
    }
}

Monsters* getMonsters(const Labyrinth* labyrinth) {
    Monsters* monsters = malloc(sizeof(Monsters));
    monsters->monstersHits = 0;
    monsters->penalityCount = 0;

    int maxCount = 10;
    monsters->count = 0;
    monsters->monsters = malloc(sizeof(Monster*) * maxCount);

    for (size_t line = 0; line < labyrinth->height; line++) {
        for (size_t col = 0; col < labyrinth->width; col++) {
            if (monsters->count == maxCount) {
                maxCount *= 2;
                monsters->monsters = realloc(monsters->count, sizeof(Monster*) * maxCount);
            }

            switch (getSquare(labyrinth, line, col)) {
                case SQU_OGRE:
                    monsters->monsters[monsters->count] = (Monster*) createOgre(line, col, labyrinth);
                    monsters->count++;
                    break;
                case SQU_SPECTRUM:
                case SQU_SPECTRUM_IN_WALL:
                    monsters->monsters[monsters->count] = (Monster*) createSpectrum(line, col);
                    monsters->count++;
                    break;
                default:
                    continue;
            }
        }
    }

    return monsters;
}

void moveMonsters(Labyrinth* labyrinth, Monsters* monsters);

void destroyMonsters(Monsters* monsters) {
    for (size_t i = 0; i < monsters->count; i++) {
        monsters->monsters[i]->destroy(monsters->monsters[i]);
    }
    monsters->count = 0;

    free(monsters->monsters);
    monsters->monsters = NULL;

    free(monsters);
}
