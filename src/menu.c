#include "menu.h"

#include <stdio.h>
#include <string.h>

#include "game.h"
#include "labyrinth.h"
#include "labyrinth_generator.h"
#include "labyrinth_repository.h"
#include "leaderboard.h"
#include "user_interface.h"
#include "monsters.h"

// Defines ----------------------------------------------------------------------------------------

#define LABYRINTH_NAME_LENGTH 40
#define LABYRINTH_COUNT_MAX 100
#define SCORE_COUNT_MAX 10

// Prototypes statiques ---------------------------------------------------------------------------

/**
 * @brief Supprime le labyrinthe actuellement chargé depuis le menu.
 *
 * @param menu Pointeur vers le menu contenant le labyrinthe à détruire.
 */
static void destroyLabyrinthFromMenu(Menu* menu);

// Implémentations statiques ----------------------------------------------------------------------

static void destroyLabyrinthFromMenu(Menu* menu) {
    if (menu->labyrinth == NULL) {
        return;
    }

    destroyLabyrinth(menu->labyrinth);
    menu->labyrinth = NULL;
}

// Implémentations --------------------------------------------------------------------------------

Menu* createMenu() {
    Menu* menu = malloc(sizeof(Menu));
    menu->labyrinth = NULL;

    return menu;
}

void destroyMenu(Menu* menu) {
    if (menu == NULL) {
        return;
    }

    destroyLabyrinthFromMenu(menu);
    free(menu);
}

void createLabyrinthAction(Menu* menu) {
    // Récupère les informations de l'utilisateur
    size_t height;
    size_t width;
    char* name = malloc(LABYRINTH_NAME_LENGTH * sizeof(char));
    int monsters;
    displayLabyrinthGenerationForm(&height, &width, name, LABYRINTH_NAME_LENGTH, &monsters);

    // Génération et svg du labyrinthe
    Labyrinth* labyrinth = generateLabyrinth(height, width);
    printf("labyrinthe généré\n");

    addObjectsInLabyrinth(labyrinth);
    labyrinth->name = name;

    if (monsters) {
        addMonsters(labyrinth);
        labyrinth->monsters = 1;
    }

    saveLabyrinth(name, labyrinth);

    // On enregistre le labyrinthe dans le menu
    if (menu->labyrinth != NULL) {
        destroyLabyrinthFromMenu(menu);
    }

    menu->labyrinth = labyrinth;
}

void loadLabyrinthAction(Menu* menu) {
    // Créé les données
    char** names = malloc(sizeof(char*) * LABYRINTH_COUNT_MAX);
    for (int i = 0; i < LABYRINTH_COUNT_MAX; i++) {
        names[i] = malloc(sizeof(char) * LABYRINTH_NAME_LENGTH);
    }

    //  Récupère les données
    int count = getLabyrinthsNames(names, LABYRINTH_COUNT_MAX, LABYRINTH_NAME_LENGTH);
    int index = displayLabyrintsAvailable(names, count);

    char* name = NULL;
    if (index >= 0) {
        name = names[index];
    }

    // Détruit les noms
    for (int i = 0; i < LABYRINTH_COUNT_MAX; i++) {
        if (i != index) {
            free(names[i]);
        }
    }
    free(names);

    // Effectue l'action choisi.
    if (index < 0) {
        return;
    }

    if (menu->labyrinth != NULL) {
        destroyLabyrinthFromMenu(menu);
    }

    menu->labyrinth = loadLabyrinth(name);
    free(name);
}

void playGameAction(Menu* menu) {
    // Joue au Jeu
    Game* game = startGame(menu->labyrinth);
    
    while(!isGameOver(game)) {
        Direction direction;
        do {
            direction = displayGame(game);
        } while (!move(game, direction));
    }

    // Game over
    Leaderboard* leaderboard = loadLeaderboard(game->labyrinth->name);
    if (leaderboard == NULL) {
        leaderboard = createLeaderboard(SCORE_COUNT_MAX);
    }

    int position = getLeaderboardPosition(leaderboard, game->score);
    if (position >= 0) {
        char playerName[PLAYER_NAME_LENGTH];
        displayGameOver(game, leaderboard, playerName);

        Score score;
        strcpy(score.playerName, playerName);
        score.score = game->score;

        updateLeaderboard(leaderboard, score);

        saveLeaderboard(game->labyrinth->name, leaderboard);
    } else {
        displayGameOver(game, leaderboard, NULL);
    }

    destroyLeaderboard(leaderboard);
    endGame(game);

    // Recharge le labyrinthe
    Labyrinth* new = loadLabyrinth(menu->labyrinth->name);
    destroyLabyrinthFromMenu(menu);
    menu->labyrinth = new;
}

void showScoresAction(Menu* menu) {
    Leaderboard* leaderboard = loadLeaderboard(menu->labyrinth->name);
    
    displayLeaderboard(menu->labyrinth->name, leaderboard);

    destroyLeaderboard(leaderboard);
}
