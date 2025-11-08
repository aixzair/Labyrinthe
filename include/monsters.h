#ifndef MONSTERS
#define MONSTERS

#include <stdlib.h>

#include "labyrinth.h"
#include "position.h"

// Structs ----------------------------------------------------------------------------------------

typedef struct Monster {
    Position position;
    void (*move)(struct Monster* self, Labyrinth* labyrinth, int penality);
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
    int penalityCount;
} Monsters;

// Prototypes -------------------------------------------------------------------------------------

/**
 * @brief Ajoute des monstres dans le labyrinthe.
 *
 * @param labyrinth Pointeur vers le labyrinthe.
 */
void addMonsters(Labyrinth* labyrinth);

/**
 * @brief Récupère la liste des monstres du labyrinthe.
 *
 * @param labyrinth Pointeur vers le labyrinthe.
 * @return Pointeur vers la structure Monsters.
 */
Monsters* getMonsters(const Labyrinth* labyrinth);

/**
 * @brief Vérifie si une position contient un monstre.
 *
 * @param labyrinth Pointeur vers le labyrinthe.
 * @param position Position à vérifier.
 * @return 1 si un monstre est présent, 0 sinon.
 */
int isMonster(const Labyrinth* labyrinth, Position position);

/**
 * @brief Supprime un monstre à une position donnée.
 *
 * @param monsters Pointeur vers la structure des monstres.
 * @param position Position du monstre à supprimer.
 */
void killMonster(Monsters* monsters, Position position);

/**
 * @brief Déplace tous les monstres dans le labyrinthe.
 *
 * @param labyrinth Pointeur vers le labyrinthe.
 * @param monsters Pointeur vers la structure des monstres.
 */
void moveMonsters(Labyrinth* labyrinth, Monsters* monsters);

/**
 * @brief Libère la mémoire allouée pour les monstres.
 *
 * @param monsters Pointeur vers la structure des monstres à détruire.
 */
void destroyMonsters(Monsters* monsters);

#endif
