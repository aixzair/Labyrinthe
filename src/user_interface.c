#include "user_interface.h"

#include <stdio.h>

#include "inputs.h"

#define Z_KEY 'z'
#define S_KEY 's'
#define Q_KEY 'q'
#define D_KEY 'd'

static void resetDisplay();

static char getLabyrinthChar(Square square);

static void displayLabyrinth(const Labyrinth* labyrinth);



static void resetDisplay() {
    system("clear");
}

static char getLabyrinthChar(Square square) {
    switch (square) {
        case SQU_PLAYER: return 'o';
        case SQU_CORRIDOR: return ' ';
        case SQU_END: return '-';

        case SQU_DOOR: return 'D';
        case SQU_KEY: return 'k';
        case SQU_COIN: return '*';
        case SQU_TRAP: return '^';

        // NOTE : SQU_WALL
        default: return '#';
    }
}

static void displayLabyrinth(const Labyrinth* labyrinth) {
    for (size_t line = 0; line < labyrinth->height; line++) {
        for (size_t col = 0; col < labyrinth->width; col++) {
            printf("%c ", getLabyrinthChar(labyrinth->squares[line][col]));
        }
        printf("\n");
    }
}



Action displayMenu(const Menu* menu) {
    int playAvailable = menu->labyrinth != NULL;

    resetDisplay();
    if (playAvailable) {
        printf("Labyrinthe : %s\n\n", menu->labyrinth->name);
        displayLabyrinth(menu->labyrinth);
        printf("\n");
    }

    printf("Menu :\n");
    printf("1. Créer un labyrinthe\n");
    printf("2. Charger un larbyrinthe\n");
    if (playAvailable) {
        printf("3. Jouer\n");
    }
    printf("4. Quiter\n");


    int choice;
    if (playAvailable) {
        choice = askForIntInRange(1, 4);
    } else {
        int choices[] = {1, 2, 4};
        choice = askForIntInList(choices, 3);
    }

    switch (choice) {
        case 1: return ACT_CREATE;
        case 2: return ACT_LOAD;
        case 3: return ACT_PLAY;
        default: return ACT_QUIT;
    }
}

void displayLabyrinthGenerationForm(size_t* height, size_t* width, char* name, size_t nameLength) {
    resetDisplay();

    printf("Création d'un labyrinthe\n");

    printf("Hauteur du labyrinthe, impaire [5 ; 99]\n");
    do {
        *height = askForIntInRange(5, 99);
    } while (*height % 2 == 0);

    printf("Largeur du labyrinthe, impaire [5 ; 99]\n");
    do {
        *width = askForIntInRange(5, 99);
    } while (*width % 2 == 0);

    printf("Nom du labyrinthe, max 40 caractères\n");
    askForString(name, nameLength);
}

int displayLabyrintsAvailable(char** names, int count) {
    resetDisplay();

    printf("Labyrinthes disponibles :\n");
    for (int i = 0; i < count; i++) {
        printf("%d : %s\n", i + 1, names[i]);
    }

    printf("\nIndice du labyrinthe (0 : quitter) :\n");
    
    return askForIntInRange(0, count) - 1;
}

Direction displayGame(const Game* game) {
    resetDisplay();
    printf("Labyrinthe : %s. Score %d.\n", game->labyrinth->name, game->score);
    displayLabyrinth(game->labyrinth);

    char values[] = {Z_KEY, S_KEY, Q_KEY, D_KEY};
    char value = fastAskForCharInList(values, 4);

    switch (value) {
        case Z_KEY: return DIR_UP;
        case S_KEY: return DIR_DOWN;
        case Q_KEY: return DIR_LEFT;
        default: return DIR_RIGHT;
    }
}

void displayGameOver(const Game* game) {
    resetDisplay();
    printf("Partie terminé.\n");
    printf("Score : %d.\n", game->score);
    fastAskForChar();
}
