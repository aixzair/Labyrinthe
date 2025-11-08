#include "labyrinth_generator.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Defines ----------------------------------------------------------------------------------------

#define MATRICE_WALL -1
#define MAX_TRY 1000

// Structs ----------------------------------------------------------------------------------------

typedef struct {
    int groupCount;
    size_t lines;
    size_t cols;
    int** values;
} Matrice;

// Prototypes statiques ---------------------------------------------------------------------------

/**
 * @brief Génère un entier aléatoire dans un intervalle donné.
 *
 * @param min Valeur minimale incluse.
 * @param max Valeur maximale incluse.
 * @return Entier aléatoire compris entre min et max.
 */
static int randomInt(int min, int max);

/**
 * @brief Crée une nouvelle matrice de taille spécifiée.
 *
 * @param lines Nombre de lignes.
 * @param cols Nombre de colonnes.
 * @return Nouvelle matrice initialisée.
 */
static Matrice newMatrice(size_t lines, size_t cols);

/**
 * @brief Libère la mémoire allouée pour une matrice.
 *
 * @param matrice Pointeur vers la matrice à détruire.
 */
static void destroyMatrice(Matrice* matrice);

/**
 * @brief Cherche une position interne pour fusion dans une matrice.
 *
 * @param matrice Pointeur vers la matrice.
 * @param line Pointeur pour stocker la ligne trouvée.
 * @param col Pointeur pour stocker la colonne trouvée.
 * @return 1 si une position est trouvée, 0 sinon.
 */
static int findInnerPlaceToMerge(const Matrice* matrice, size_t* line, size_t* col);

/**
 * @brief Fusionne une position spécifique dans une matrice.
 *
 * @param matrice Pointeur vers la matrice.
 * @param line Ligne de la position à fusionner.
 * @param col Colonne de la position à fusionner.
 * @return 1 si la fusion réussit, 0 sinon.
 */
static int mergePlace(const Matrice* matrice, size_t line, size_t col);

/**
 * @brief Génère une nouvelle matrice initialisée de taille donnée.
 *
 * @param lines Nombre de lignes.
 * @param cols Nombre de colonnes.
 * @return Nouvelle matrice générée.
 */
static Matrice generateMatrice(size_t lines, size_t cols);

/**
 * @brief Crée un nouveau labyrinthe à partir d'une matrice.
 *
 * @param matrice Matrice utilisée pour générer le labyrinthe.
 * @return Pointeur vers le labyrinthe créé.
 */
static Labyrinth* newLabyrinthFromMatrice(Matrice matrice);

/**
 * @brief Cherche une case aléatoire de type spécifique dans le labyrinthe.
 *
 * @param labyrinth Pointeur vers le labyrinthe.
 * @param type Type de case recherché.
 * @param line Pointeur pour stocker la ligne trouvée.
 * @param col Pointeur pour stocker la colonne trouvée.
 * @return 1 si une case est trouvée, 0 sinon.
 */
static int findRamdomSquare(const Labyrinth* labyrinth, Square type, size_t* line, size_t* col);

// Implémentations statiques ----------------------------------------------------------------------

static int randomInt(int min, int max) {
    int range = max - min + 1;

    return (rand() % range) + min; 
}

static Matrice newMatrice(size_t lines, size_t cols) {
    Matrice matrice;

    matrice.lines = lines;
    matrice.cols = cols;
    matrice.groupCount = 0;

    matrice.values = (int**) malloc(lines * sizeof(int*));
    for (size_t line = 0; line < lines; line++) {
        matrice.values[line] = (int*) malloc(cols * sizeof(int));

        for (size_t col = 0; col < matrice.cols; col++) {
            if (line % 2 == 1 && col % 2 == 1) {
                matrice.values[line][col] = matrice.groupCount;
                matrice.groupCount++;
            } else {
                matrice.values[line][col] = MATRICE_WALL;
            }
        }
    }

    return matrice;
}

static void destroyMatrice(Matrice* matrice) {
    for (size_t line = 0; line < matrice->lines; line++) {
        free(matrice->values[line]);
    }
    free(matrice->values);
}

static int findInnerPlaceToMerge(const Matrice* matrice, size_t* line, size_t* col) {
    const int lineMin = 1;
    const int lineMax = matrice->lines - 2;

    const int colMin = 1;
    const int colMax = matrice->cols - 2;

    for (int try = 0; try < MAX_TRY; try++) {
        *line = randomInt(lineMin, lineMax);
        *col = randomInt(colMin, colMax);

        // Vérifie que c'est un mur
        if (matrice->values[*line][*col] != MATRICE_WALL) {
            continue;
        }

        // Vérifie qu'il y a deux groupe différents à coté
        int values[] = {
            matrice->values[*line + 1][*col],
            matrice->values[*line - 1][*col],
            matrice->values[*line][*col + 1],
            matrice->values[*line][*col - 1]
        };

        int value = MATRICE_WALL;
        for (int i = 0; i < 4; i++) {
            if (values[i] == MATRICE_WALL) {
                continue;
            }

            if (value == MATRICE_WALL) {
                value = values[i];
            } else if (value != values[i]) {
                return 1;
            }
        }
    }

    return 0;
}

static int mergePlace(const Matrice* matrice, size_t line, size_t col) {
    if (matrice->values[line][col] != MATRICE_WALL) {
        return 0;
    }

    // Change les valeurs
    int value = MATRICE_WALL;

    int closeSquares[] = {
        matrice->values[line + 1][col],
        matrice->values[line - 1][col],
        matrice->values[line][col + 1],
        matrice->values[line][col - 1]
    };

    for (int i = 0; i < 4; i++) {
        if (closeSquares[i] != MATRICE_WALL) {
            if (value == MATRICE_WALL) {
                value = closeSquares[i];
                continue;
            }

            int valueToChange = closeSquares[i];
            for (size_t l = 0; l < matrice->lines; l++) {
                for (size_t c = 0; c < matrice->cols; c++) {
                    if (matrice->values[l][c] == valueToChange) {
                        matrice->values[l][c] = value;
                    }
                }
            }
        }
    }

    // Vérifie que des valeurs ont étaits changé
    if (value == MATRICE_WALL) {
        return 0;
    }

    matrice->values[line][col] = value;

    return 1;
}

static Matrice generateMatrice(size_t height, size_t width) {
    Matrice matrice = newMatrice(height, width);

    while (matrice.groupCount > 1) {
        size_t line;
        size_t col;

        if (!findInnerPlaceToMerge(&matrice, &line, &col)) {
            break;
        }

        if (!mergePlace(&matrice, line, col)) {
            break;
        }
    }

    return matrice;
}

static Labyrinth* newLabyrinthFromMatrice(Matrice matrice) {
    Labyrinth* labyrinth = malloc(sizeof(Labyrinth));
    labyrinth->name = NULL;
    labyrinth->height = matrice.lines;
    labyrinth->width = matrice.cols;
    labyrinth->monsters = 0;

    labyrinth->squares = (Square**) malloc(matrice.lines * sizeof(Square*));
    for (size_t line = 0; line < matrice.lines; line++) {
        labyrinth->squares[line] = (Square*) malloc(matrice.cols * sizeof(Square));

        for (size_t col = 0; col < matrice.cols; col++) {
            if (matrice.values[line][col] == MATRICE_WALL) {
                setSquare(labyrinth, line, col, SQU_WALL);
            } else {
                setSquare(labyrinth, line, col, SQU_CORRIDOR);
            }
        }
    }

    return labyrinth;
}

static int findRamdomSquare(const Labyrinth* labyrinth, Square type, size_t* line, size_t* col) {
    for (int try = 0; try < MAX_TRY; try++) {
        *line = randomInt(1, labyrinth->height - 2);
        *col = randomInt(1, labyrinth->width - 2);

        if (type == SQU_NULL) {
            return 1;
        }

        if (labyrinth->squares[*line][*col] == type) {
            return 1;
        }
    }
    return 0;
}

// Implémentations --------------------------------------------------------------------------------

Labyrinth* generateLabyrinth(size_t height, size_t width) {
    srand(time(NULL));

    Matrice matrice = generateMatrice(height, width);
    Labyrinth* labyrinth = newLabyrinthFromMatrice(matrice);
    destroyMatrice(&matrice);

    setSquare(labyrinth, 0, 1, SQU_PLAYER);
    setSquare(labyrinth, height - 1, width - 2, SQU_END);

    return labyrinth;
}

void addObjectsInLabyrinth(Labyrinth* labyrinth) {
    srand(time(NULL));

    int coinCount = (labyrinth->height - 2) * (labyrinth->width - 2) * 0.1;
    int trapCount = (labyrinth->height - 2) * (labyrinth->width - 2) * 0.1;

    size_t line;
    size_t col;

    for (int i = 0; i < coinCount; i++) {
        if (findRamdomSquare(labyrinth, SQU_CORRIDOR, &line, &col)) {
            setSquare(labyrinth, line, col, SQU_COIN);
        }
    }

    for (int i = 0; i < trapCount; i++) {
        if (findRamdomSquare(labyrinth, SQU_CORRIDOR, &line, &col)) {
            setSquare(labyrinth, line, col, SQU_TRAP);
        }
    }

    if (findRamdomSquare(labyrinth, SQU_CORRIDOR, &line, &col)) {
        setSquare(labyrinth, line, col, SQU_KEY);

        for (size_t l = 0; l < labyrinth->height; l++) {
            for (size_t c = 0; c < labyrinth->width; c++) {
                if (getSquare(labyrinth, l, c) == SQU_END) {
                    setSquare(labyrinth, l, c, SQU_DOOR);

                    l = labyrinth->height;
                    break;
                }
            }
        }
    }
}
