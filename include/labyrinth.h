#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <stdlib.h>

// Enums ------------------------------------------------------------------------------------------

typedef enum {
    SQU_CORRIDOR,
    SQU_WALL,
    SQU_COIN,
    SQU_TRAP,
    SQU_KEY,
    SQU_DOOR,
    SQU_END,
    SQU_PLAYER,
    SQU_OGRE,
    SQU_OGRE_IN_COIN,
    SQU_OGRE_IN_TRAP,
    SQU_OGRE_IN_KEY,
    SQU_SPECTRUM,
    SQU_SPECTRUM_IN_WALL,
    SQU_SPECTRUM_IN_COIN,
    SQU_SPECTRUM_IN_TRAP,
    SQU_SPECTRUM_IN_KEY,
    SQU_NULL,
} Square;

// Structs ----------------------------------------------------------------------------------------

typedef struct {
    char* name;
    size_t height;
    size_t width;
    Square** squares;
    int monsters;
} Labyrinth;

// Prototypes -------------------------------------------------------------------------------------

/**
 * @brief Vérifie si une position dans le labyrinthe est valide.
 *
 * @param labyrinth Pointeur vers le labyrinthe.
 * @param line Ligne à vérifier.
 * @param col Colonne à vérifier.
 * @return 1 si la position est valide, 0 sinon.
 */
int isValidSquare(const Labyrinth* labyrinth, int line, int col);

/**
 * @brief Récupère la case à une position donnée dans le labyrinthe.
 *
 * @param labyrinth Pointeur vers le labyrinthe.
 * @param line Ligne de la case.
 * @param col Colonne de la case.
 * @return La case située à la position spécifiée.
 */
Square getSquare(const Labyrinth* labyrinth, int line, int col);

/**
 * @brief Modifie la case à une position donnée dans le labyrinthe.
 *
 * @param labyrinth Pointeur vers le labyrinthe.
 * @param line Ligne de la case.
 * @param col Colonne de la case.
 * @param square Nouvelle case à placer.
 * @return 1 si la modification réussit, 0 sinon.
 */
int setSquare(const Labyrinth* labyrinth, int line, int col, Square square);

/**
 * @brief Libère la mémoire allouée pour un labyrinthe.
 *
 * @param labyrinth Pointeur vers le labyrinthe à détruire.
 */
void destroyLabyrinth(Labyrinth* labyrinth);

#endif
