#ifndef LABYRINTH_REPOSITORY_H
#define LABYRINTH_REPOSITORY_H

#include "labyrinth.h"
#include "leaderboard.h"

// Prototypes -------------------------------------------------------------------------------------

/**
 * @brief Récupère les noms des labyrinthes disponibles.
 *
 * @param names Tableau pour stocker les noms.
 * @param namesLength Nombre maximum de noms à récupérer.
 * @param stringLength Taille maximale de chaque nom.
 * @return Nombre de noms récupérés, -1 en cas d'erreur.
 */
int getLabyrinthsNames(char** names, int namesLength, int stringLength);

/**
 * @brief Charge un labyrinthe à partir de son nom.
 *
 * @param labyrinthName Nom du labyrinthe à charger.
 * @return Pointeur vers le labyrinthe chargé, ou NULL en cas d'erreur.
 */
Labyrinth* loadLabyrinth(const char* labyrinthName);

/**
 * @brief Sauvegarde un labyrinthe sous un nom donné.
 *
 * @param labyrinthName Nom pour la sauvegarde.
 * @param labyrinth Pointeur vers le labyrinthe à sauvegarder.
 * @return 1 si la sauvegarde réussit, 0 sinon.
 */
int saveLabyrinth(const char* labyrinthName, const Labyrinth* labyrinth);

/**
 * @brief Charge le classement associé à un labyrinthe.
 *
 * @param labyrinthName Nom du labyrinthe.
 * @return Pointeur vers le classement chargé, ou NULL en cas d'erreur.
 */
Leaderboard* loadLeaderboard(const char* labyrinthName);

/**
 * @brief Sauvegarde le classement d'un labyrinthe.
 *
 * @param labyrinthName Nom du labyrinthe.
 * @param leaderboard Pointeur vers le classement à sauvegarder.
 * @return 1 si la sauvegarde réussit, 0 sinon.
 */
int saveLeaderboard(const char* labyrinthName, const Leaderboard* leaderboard);

#endif
