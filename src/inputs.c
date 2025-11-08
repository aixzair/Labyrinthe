#include "inputs.h"

#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

// Prototypes statiques ---------------------------------------------------------------------------

/**
 * @brief Vide le buffer d'entrée standard.
 *
 * Cette fonction est utilisée pour consommer les caractères restants
 * dans le buffer après une saisie utilisateur afin d'éviter des erreurs.
 */
static void clearBuffer();

// Implémentations statiques ----------------------------------------------------------------------

static void clearBuffer() {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

// Implémentations --------------------------------------------------------------------------------

char askForChar() {
    char input = getchar();
    clearBuffer();
    return input;
}

char askForCharInList(char* values, int n) {
    char input;

    while (1) {
        input = askForChar();

        for (int i = 0; i < n; i++) {
            if (values[i] == input) {
                return input;
            }
        }
    }
}


int askForInt() {
    int input;

    while (!scanf("%d", &input)) {
        clearBuffer();
    }
    clearBuffer();

    return input;
}

int askForIntInList(int* values, int n) {
    int input;
    int success = 0;

    while (!success) {
        input = askForInt();

        for (int i = 0; i < n; i++) {
            if (values[i] == input) {
                success = 1;
                break;
            }
        }
    }

    return input;
}

int askForIntInRange(int min, int max) {
    if (min > max) {
        int temp = min;
        min = max;
        max = temp;
    }

    int input;

    do {
        input = askForInt();
    } while (input < min || input > max);

    return input;
}

void askForString(char *string, size_t length) {
    // Paramètres invalides
    if (string == NULL || length == 0) {
        return;
    }

    // Entrée invalide
    if (fgets(string, length, stdin) == NULL) {
        string[0] = '\0';
        clearBuffer();
        return;
    }

    // Gère la gin de la chaine
    size_t len = strlen(string);
    if (len > 0 && string[len - 1] == '\n') {
        string[len - 1] = '\0';
    } else {
        clearBuffer();
    }
}


char fastAskForChar() {
    // Sauvegarde l'ancien terminal
    struct termios old;
    tcgetattr(STDIN_FILENO, &old);

    // Change le mode du terminal
    struct termios temp;
    temp = old;
    temp.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &temp);

    // Récupère la valeur
    char input = getchar();

    // Remet l'ancien terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &old);

    return input;
}

char fastAskForCharInList(char * values, int n) {
    char input;

    while (1) {
        input = fastAskForChar();

        for (int i = 0; i < n; i++) {
            if (values[i] == input) {
                return input;
            }
        }
    }
}
