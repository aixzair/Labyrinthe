#ifndef MENU_H
#define MENU_H

#include "labyrinth.h"

// Enums ------------------------------------------------------------------------------------------

typedef enum {
    ACT_CREATE,
    ACT_LOAD,
    ACT_PLAY,
    ACT_SCORE,
    ACT_QUIT
} Action;

// Structs ----------------------------------------------------------------------------------------

typedef struct {   
    Labyrinth* labyrinth;
} Menu;

// Prototypes -------------------------------------------------------------------------------------

/**
 * @brief Crée un menu.
 *
 * @return Pointeur vers le menu créé.
 */
Menu* createMenu();

/**
 * @brief Libère la mémoire allouée pour un menu.
 *
 * @param menu Pointeur vers le menu à détruire.
 */
void destroyMenu(Menu* menu);

/**
 * @brief Action pour créer un labyrinthe depuis le menu.
 *
 * @param menu Pointeur vers le menu.
 */
void createLabyrinthAction(Menu* menu);

/**
 * @brief Action pour charger un labyrinthe depuis le menu.
 *
 * @param menu Pointeur vers le menu.
 */
void loadLabyrinthAction(Menu* menu);

/**
 * @brief Action pour lancer une partie depuis le menu.
 *
 * @param menu Pointeur vers le menu.
 */
void playGameAction(Menu* menu);

/**
 * @brief Action pour afficher les scores depuis le menu.
 *
 * @param menu Pointeur vers le menu.
 */
void showScoresAction(Menu* menu);

#endif
