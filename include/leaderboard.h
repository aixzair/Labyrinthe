#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "score.h"

// Structs ----------------------------------------------------------------------------------------

typedef struct {
    int count;
    int countMax;
    Score* scores;
} Leaderboard;

// Prototypes -------------------------------------------------------------------------------------

/**
 * @brief Crée un classement pouvant contenir un certain nombre d'entrées.
 *
 * @param count Nombre d'entrées du classement.
 * @return Pointeur vers le classement créé.
 */
Leaderboard* createLeaderboard(int count);

/**
 * @brief Détermine la position d'un score dans le classement.
 *
 * @param leaderboard Pointeur vers le classement.
 * @param score Score à évaluer.
 * @return Position du score dans le classement, -1 si hors classement.
 */
int getLeaderboardPosition(const Leaderboard* leaderboard, int score);

/**
 * @brief Met à jour le classement avec un nouveau score.
 *
 * @param leaderboard Pointeur vers le classement.
 * @param score Score à ajouter ou mettre à jour.
 * @return 1 si le classement a été modifié, 0 sinon.
 */
int updateLeaderboard(Leaderboard* leaderboard, Score score);

/**
 * @brief Libère la mémoire allouée pour un classement.
 *
 * @param leaderboard Pointeur vers le classement à détruire.
 */
void destroyLeaderboard(Leaderboard* leaderboard);

#endif
