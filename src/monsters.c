#include "monsters.h"

#include <stdlib.h>

static int randomInt(int min, int max);

static Spectrum* createSpectrum(int line, int col);

static void destroySpectrum(Monster* monster);

static Ogre* createOgre(int line, int col, const Labyrinth* labyrinth);

static void destroyOgre(Monster* monster);

static void moveSpectrum(Monster* monster, Labyrinth* labyrinth, int penality);

static Square lastSpectrumPosition(Square square);

static Square newSpectrumPosition(Square square);

static void moveOgre(Monster* monster, Labyrinth* labyrinth, int penality);


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

static void moveSpectrum(Monster* monster, Labyrinth* labyrinth, int penality) {
    Spectrum* spectrum = (Spectrum*) monster;
    spectrum->speed = penality / 5 + 1;
    
    for (int i = 0; i < spectrum->speed; i++) {
        int success = 0;
        do {
            int direction = randomInt(1, 4);

            // Nouvelle position
            Position newPosition;
            switch (direction) {
                case 1:
                    newPosition.x = monster->position.x + 1;
                    newPosition.y = monster->position.y;
                    break;
                case 2:
                    newPosition.x = monster->position.x - 1;
                    newPosition.y = monster->position.y;
                    break;
                case 3:
                    newPosition.x = monster->position.x;
                    newPosition.y = monster->position.y + 1;
                    break;
                default:
                    newPosition.x = monster->position.x;
                    newPosition.y = monster->position.y - 1;
            }

            // Se déplace
            Square newSquare = getSquare(labyrinth, newPosition.y, newPosition.x);
            Square lastSquare = getSquare(labyrinth, monster->position.y, monster->position.x);

            switch (newSquare) {
                case SQU_CORRIDOR:
                case SQU_WALL:
                case SQU_COIN:
                case SQU_TRAP:
                case SQU_KEY:
                        setSquare(
                            labyrinth,
                            newPosition.y,
                            newPosition.x, 
                            newSpectrumPosition(newSquare)
                        );
                        setSquare(
                            labyrinth,
                            monster->position.y,
                            monster->position.x,
                            lastSpectrumPosition(lastSquare)
                        );
                        monster->position = newPosition;
                        success = 1;
                    break;
                default:
                    continue;
            }
        } while (!success);
    }
}

static Square lastSpectrumPosition(Square square) {
    switch (square) {
        case SQU_SPECTRUM: return SQU_CORRIDOR;
        case SQU_SPECTRUM_IN_COIN: return SQU_COIN;
        case SQU_SPECTRUM_IN_KEY: return SQU_KEY;
        case SQU_SPECTRUM_IN_TRAP: return SQU_TRAP;
        case SQU_SPECTRUM_IN_WALL: return SQU_WALL;
        default: return SQU_NULL;
    }
}

static Square newSpectrumPosition(Square square) {
    switch (square) {
        case SQU_CORRIDOR: return SQU_SPECTRUM;
        case SQU_COIN: return SQU_SPECTRUM_IN_COIN;
        case SQU_KEY: return SQU_SPECTRUM_IN_KEY;
        case SQU_TRAP: return SQU_SPECTRUM_IN_TRAP;
        case SQU_WALL: return SQU_SPECTRUM_IN_WALL;
        default: return SQU_WALL;
    }
}

static void moveOgre(Monster* monster, Labyrinth* labyrinth, int penality) {
    Ogre* ogre = (Ogre*) monster;
    ogre->distance = 3 * penality + 1;

    // Récupère la direction
    Position newPosition;

    if (
        
    ) {
        // Si il est dans sa zone
    } else {
        // Si il est hors de sa zone
    }
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
                case SQU_OGRE_IN_COIN:
                case SQU_OGRE_IN_TRAP:
                case SQU_OGRE_IN_KEY:
                    monsters->monsters[monsters->count] = (Monster*) createOgre(line, col, labyrinth);
                    monsters->count++;
                    break;
                case SQU_SPECTRUM:
                case SQU_SPECTRUM_IN_WALL:
                case SQU_SPECTRUM_IN_COIN:
                case SQU_SPECTRUM_IN_TRAP:
                case SQU_SPECTRUM_IN_KEY:
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
