#ifndef LABYRINTH_GENERATOR_H
#define LABYRINTH_GENERATOR_H

#include "labyrinth.h"

// Prototypes -------------------------------------------------------------------------------------

/**
 * @brief Génère un labyrinthe de taille donnée.
 *
 * @param height Hauteur du labyrinthe > 5 et impaire.
 * @param width Largeur du labyrinthe > 5 et impaire.
 * @return Pointeur vers le labyrinthe généré.
 */
Labyrinth* generateLabyrinth(size_t height, size_t width);

/**
 * @brief Ajoute des objets (clé, porte, pièces, pièges) dans le labyrinthe.
 *
 * @param labyrinth Pointeur vers le labyrinthe.
 */
void addObjectsInLabyrinth(Labyrinth* labyrinth);

#endif
