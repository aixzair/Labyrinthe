#include "monsters.h"

#include <stdlib.h>
#include <time.h>

#include "direction.h"

// Defines ----------------------------------------------------------------------------------------

#define MAX_TRY 4

// Prototypes statiques ---------------------------------------------------------------------------

/**
 * @brief Génère un entier aléatoire dans un intervalle donné.
 *
 * @param min Valeur minimale incluse.
 * @param max Valeur maximale incluse.
 * @return Entier aléatoire compris entre min et max.
 */
static int randomInt(int min, int max);

/**
 * @brief Crée un spectre à une position donnée.
 *
 * @param line Ligne de départ du spectre.
 * @param col Colonne de départ du spectre.
 * @return Pointeur vers le spectre créé.
 */
static Spectrum* createSpectrum(int line, int col);

/**
 * @brief Libère la mémoire allouée pour un spectre.
 *
 * @param monster Pointeur vers le spectre à détruire.
 */
static void destroySpectrum(Monster* monster);

/**
 * @brief Crée un ogre à une position donnée.
 *
 * @param line Ligne de départ de l'ogre.
 * @param col Colonne de départ de l'ogre.
 * @return Pointeur vers l'ogre créé.
 */
static Ogre* createOgre(int line, int col);

/**
 * @brief Libère la mémoire allouée pour un ogre.
 *
 * @param monster Pointeur vers l'ogre à détruire.
 */
static void destroyOgre(Monster* monster);

/**
 * @brief Déplace un spectre dans le labyrinthe avec pénalité.
 *
 * @param monster Pointeur vers le spectre à déplacer.
 * @param labyrinth Pointeur vers le labyrinthe.
 * @param penality Pénalité à appliquer lors du déplacement.
 */
static void moveSpectrum(Monster* monster, Labyrinth* labyrinth, int penality);

/**
 * @brief Récupère le type de case correspondant à une case avec un spectre.
 *
 * @param square Case actuelle du spectre.
 * @return Case correspondant à l'état précédent.
 */
static Square lastSpectrumSquare(Square square);

/**
 * @brief Récupère le type de case correspondant à l'état sans spectre.
 *
 * @param square Case actuelle du spectre.
 * @return Case correspondant à l'état futur.
 */
static Square newSpectrumSquare(Square square);

/**
 * @brief Déplace un ogre dans le labyrinthe avec pénalité.
 *
 * @param monster Pointeur vers l'ogre à déplacer.
 * @param labyrinth Pointeur vers le labyrinthe.
 * @param penality Pénalité à appliquer lors du déplacement.
 */
static void moveOgre(Monster* monster, Labyrinth* labyrinth, int penality);

/**
 * @brief Récupère le type de case correspondant à une case sans ogre.
 *
 * @param square Case actuelle de l'ogre.
 * @return Case correspondant à l'état précédent.
 */
static Square lastOgreSquare(Square square);

/**
 * @brief Récupère le type de case correspondant à une case avec ogre.
 *
 * @param square Case actuelle de l'ogre.
 * @return Case correspondant à l'état futur.
 */
static Square newOgreSquare(Square square);

/**
 * @brief Calcule la position suivante à partir d'une position et d'une direction.
 *
 * @param position Position actuelle.
 * @param direction Direction du déplacement.
 * @return Nouvelle position après déplacement.
 */
static Position nextPosition(Position position, Direction direction);

// Implémentations statiques ----------------------------------------------------------------------

static int randomInt(int min, int max) {
    int range = max - min + 1;

    return (rand() % range) + min; 
}

static Spectrum* createSpectrum(int line, int col) {
    Spectrum* spectrum = malloc(sizeof(Spectrum));

    spectrum->base.move = moveSpectrum;
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

static Ogre* createOgre(int line, int col) {
    Ogre* ogre = malloc(sizeof(Ogre));

    ogre->base.move = moveOgre;
    ogre->base.destroy = destroyOgre;
    ogre->base.position.y = line;
    ogre->base.position.x = col;

    ogre->distance = 3;
    ogre->coin.y = line;
    ogre->coin.x = col;

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
        Position newPosition;
        Square newSquare;
        Square lastSquare;

        // Nouvelle position
        int direction = randomInt(0, 3);

        int try;
        for (try = 0; try < MAX_TRY; try++) {
            newPosition = nextPosition(monster->position, direction);
            newSquare = newSpectrumSquare(getSquare(
                labyrinth, newPosition.y, newPosition.x
            ));
            lastSquare = lastSpectrumSquare(getSquare(
                labyrinth, monster->position.y, monster->position.x
            ));

            if (newSquare != SQU_NULL && lastSquare != SQU_NULL) {
                break;
            }
            
            direction = (direction + 1) % 4;
        }

        if (try == MAX_TRY) {
            return;
        }

        // Se déplace
        setSquare(
            labyrinth, newPosition.y, newPosition.x, newSquare
        );
        setSquare(
            labyrinth, monster->position.y, monster->position.x, lastSquare
        );
        monster->position = newPosition;
    }
}

static Square lastSpectrumSquare(Square square) {
    switch (square) {
        case SQU_SPECTRUM: return SQU_CORRIDOR;
        case SQU_SPECTRUM_IN_COIN: return SQU_COIN;
        case SQU_SPECTRUM_IN_KEY: return SQU_KEY;
        case SQU_SPECTRUM_IN_TRAP: return SQU_TRAP;
        case SQU_SPECTRUM_IN_WALL: return SQU_WALL;
        default: return SQU_NULL;
    }
}

static Square newSpectrumSquare(Square square) {
    switch (square) {
        case SQU_CORRIDOR: return SQU_SPECTRUM;
        case SQU_COIN: return SQU_SPECTRUM_IN_COIN;
        case SQU_KEY: return SQU_SPECTRUM_IN_KEY;
        case SQU_TRAP: return SQU_SPECTRUM_IN_TRAP;
        case SQU_WALL: return SQU_SPECTRUM_IN_WALL;
        default: return SQU_NULL;
    }
}

static Square lastOgreSquare(Square square) {
    switch (square) {
        case SQU_OGRE: return SQU_CORRIDOR;
        case SQU_OGRE_IN_COIN: return SQU_COIN;
        case SQU_OGRE_IN_KEY: return SQU_KEY;
        case SQU_OGRE_IN_TRAP: return SQU_TRAP;
        default: return SQU_NULL;
    }
}

static Square newOgreSquare(Square square) {
    switch (square) {
        case SQU_CORRIDOR: return SQU_OGRE;
        case SQU_COIN: return SQU_OGRE_IN_COIN;
        case SQU_KEY: return SQU_OGRE_IN_KEY;
        case SQU_TRAP: return SQU_OGRE_IN_TRAP;
        default: return SQU_NULL;
    }
}

static void moveOgre(Monster* monster, Labyrinth* labyrinth, int penality) {
    Ogre* ogre = (Ogre*) monster;
    ogre->distance = 3 * penality + 1;

    // Vérifie si il est dans la zone
    Direction direction;
    if (monster->position.x < ogre->coin.x - ogre->distance) {
        direction = DIR_RIGHT; 
    } else if (monster->position.y > ogre->coin.y + ogre->distance) {
        direction = DIR_UP;
    } else if (monster->position.x > ogre->coin.x + ogre->distance) {
        direction = DIR_LEFT;
    } else if (monster->position.y < ogre->coin.y - ogre->distance) {
        direction = DIR_DOWN;
    } else {
        direction = randomInt(0, 3);
    }

    // Nouvel position
    Position newPosition;
    Square newSquare;
    Square lastSquare;

    int try;
    for (try = 0; try < MAX_TRY; try++) {
        newPosition = nextPosition(monster->position, direction);
        newSquare = newOgreSquare(getSquare(
            labyrinth, newPosition.y, newPosition.x
        ));
        lastSquare = lastOgreSquare(getSquare(
            labyrinth, monster->position.y, monster->position.x
        ));

        if (newSquare != SQU_NULL && lastSquare != SQU_NULL) {
            break;
        }
        
        direction = (direction + 1) % 4;
    }

    if (try == MAX_TRY) {
        return;
    }

    // Se déplace
    setSquare(
        labyrinth, newPosition.y, newPosition.x, newSquare
    );
    setSquare(
        labyrinth, monster->position.y, monster->position.x, lastSquare
    );
    monster->position = newPosition;
}

static Position nextPosition(Position position, Direction direction) {
    Position newPosition;
    switch (direction) {
        case DIR_RIGHT:
            newPosition.x = position.x + 1;
            newPosition.y = position.y;
            break;
        case DIR_LEFT:
            newPosition.x = position.x - 1;
            newPosition.y = position.y;
            break;
        case DIR_DOWN:
            newPosition.x = position.x;
            newPosition.y = position.y + 1;
            break;
        default:
            newPosition.x = position.x;
            newPosition.y = position.y - 1;
    }

    return newPosition;
}

// Implémentations --------------------------------------------------------------------------------

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

            if (getSquare(labyrinth, line, col) != SQU_COIN) {
                continue;
            }

            success = setSquare(labyrinth, line, col, SQU_OGRE_IN_COIN);
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

    size_t maxCount = 10;
    monsters->count = 0;
    monsters->monsters = malloc(sizeof(Monster*) * maxCount);

    for (size_t line = 0; line < labyrinth->height; line++) {
        for (size_t col = 0; col < labyrinth->width; col++) {
            if (monsters->count == maxCount) {
                maxCount *= 2;
                monsters->monsters = realloc(monsters->monsters, sizeof(Monster*) * maxCount);
            }

            switch (getSquare(labyrinth, line, col)) {
                case SQU_OGRE_IN_COIN:
                    monsters->monsters[monsters->count] = (Monster*) createOgre(line, col);
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

void moveMonsters(Labyrinth* labyrinth, Monsters* monsters) {
    for (size_t i = 0; i < monsters->count; i++) {
        Monster* monster = monsters->monsters[i];
        monster->move(monster, labyrinth, monsters->penalityCount);
    }
}

void destroyMonsters(Monsters* monsters) {
    for (size_t i = 0; i < monsters->count; i++) {
        monsters->monsters[i]->destroy(monsters->monsters[i]);
    }
    monsters->count = 0;

    free(monsters->monsters);
    monsters->monsters = NULL;

    free(monsters);
}

void killMonster(Monsters* monsters, Position position) {
    // Trouve le monstre
    size_t monsterIndex;
    for (monsterIndex = 0; monsterIndex < monsters->count; monsterIndex++) {
        Position otherPosition = monsters->monsters[monsterIndex]->position;
        if (otherPosition.x == position.x && otherPosition.y == position.y) {
            break;
        }
    }

    if (monsterIndex == monsters->count) {
        return;
    }

    // Supprime le monstre
    monsters->monsters[monsterIndex]->destroy(monsters->monsters[monsterIndex]);
    if (monsterIndex != monsters->count - 1) {
        monsters->monsters[monsterIndex] = monsters->monsters[monsters->count - 1];
    }
    monsters->count--;
}

int isMonster(const Labyrinth* labyrinth, Position position) {
    Square square = getSquare(labyrinth, position.y, position.x);

    switch (square) {
        case SQU_OGRE:
        case SQU_OGRE_IN_COIN:
        case SQU_OGRE_IN_KEY:
        case SQU_OGRE_IN_TRAP:
        case SQU_SPECTRUM:
        case SQU_SPECTRUM_IN_COIN:
        case SQU_SPECTRUM_IN_KEY:
        case SQU_SPECTRUM_IN_TRAP:
        case SQU_SPECTRUM_IN_WALL:
            return 1;
        default:
            return 0;
    }
}
