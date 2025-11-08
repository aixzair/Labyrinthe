#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "game.h"
#include "leaderboard.h"
#include "menu.h"

// Prototypes -------------------------------------------------------------------------------------

/**
 * @brief Affiche le menu et retourne l'action sélectionnée.
 *
 * @param menu Pointeur vers le menu à afficher.
 * @return Action sélectionnée par l'utilisateur.
 */
Action displayMenu(const Menu* menu);

/**
 * @brief Affiche le formulaire de création d'un labyrinthe et récupère les saisies.
 *
 * @param height Pointeur pour stocker la hauteur saisie.
 * @param width Pointeur pour stocker la largeur saisie.
 * @param name Buffer pour stocker le nom du labyrinthe.
 * @param nameLength Taille maximale du nom.
 * @param monsters Pointeur pour stocker le nombre de monstres souhaité.
 */
void displayLabyrinthGenerationForm(
    size_t* height, size_t* width, char* name, size_t nameLength, int* monsters
);

/**
 * @brief Affiche la liste des labyrinthes disponibles et permet à l'utilisateur de choisir.
 *
 * @param names Tableau contenant les noms des labyrinthes.
 * @param count Nombre de labyrinthes disponibles.
 * @return Index du labyrinthe choisi.
 */
int displayLabyrintsAvailable(char** names, int count);

/**
 * @brief Affiche le jeu et récupère la direction choisie par le joueur.
 *
 * @param game Pointeur vers la partie en cours.
 * @return Direction choisie par le joueur.
 */
Direction displayGame(const Game* game);

/**
 * @brief Affiche l'écran de fin de partie avec le classement.
 *
 * @param game Pointeur vers la partie terminée.
 * @param leaderboard Pointeur vers le classement associé.
 * @param playerName Nom du joueur.
 */
void displayGameOver(const Game* game, const Leaderboard* leaderboard, char playerName[PLAYER_NAME_LENGTH]);

/**
 * @brief Affiche le classement d'un labyrinthe.
 *
 * @param labyrinthName Nom du labyrinthe.
 * @param leaderboard Pointeur vers le classement à afficher.
 */
void displayLeaderboard(const char* labyrinthName, const Leaderboard* leaderboard);

#endif
