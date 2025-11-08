#ifndef GAME_H
#define GAME_H

#include "labyrinth.h"
#include "position.h"
#include "monsters.h"
#include "direction.h"

// Structs ----------------------------------------------------------------------------------------

typedef struct {
    int score;
    int gameOver;
    Position playerPosition;
    Labyrinth* labyrinth;
    Monsters* monsters;
} Game;

// Prototypes -------------------------------------------------------------------------------------

/**
 * @brief Démarre une nouvelle partie.
 *
 * @param labyrinth Labyrinthe utilisé pour le jeu.
 * @return Pointeur vers la partie ou NULL en cas d'erreur.
 */
Game* startGame(Labyrinth* labyrinth);

/**
 * @brief Déplace le joueur dans la direction indiquée.
 *
 * @param game Partie en cours.
 * @param direction Direction du déplacement.
 * @return 1 si le déplacement est réussi, 0 sinon.
 */
int move(Game* game, Direction direction);

/**
 * @brief Vérifie si la partie est terminée.
 *
 * @param game Partie en cours.
 * @return 1 si la partie est terminée, 0 sinon.
 */
int isGameOver(Game* game);

/**
 * @brief Termine la partie et libère les ressources associées.
 *
 * @param game Partie à terminer.
 */
void endGame(Game* game);

#endif
