// make clean && make all && valgrind --leak-check=full ./bin/tests.bin 

#include <stdio.h>

#include "./../../ressources/minunit.h"


#include "game.h"
#include "inputs.h"
#include "labyrinth_generator.h"
#include "labyrinth_repository.h"
#include "monsters.h"

// Fonction utilitaire

static Labyrinth* generateLabyrinthForTest(size_t heigth, size_t width) {
    Labyrinth* labyrinth = malloc(sizeof(Labyrinth));

    labyrinth->height = heigth;
    labyrinth->width = width;
    labyrinth->name = NULL;
    labyrinth->squares = malloc(sizeof(Square*) * heigth);
    labyrinth->monsters = 0;

    for (size_t line = 0; line < heigth; line++) {
        labyrinth->squares[line] = malloc(sizeof(width) * width);
        for (size_t col = 0; col < width; col++) {
            Square square;
            if (line == 0 || line == heigth - 1) {
                square = SQU_WALL;
            } else if (col == 0 || col == width - 1) {
                square = SQU_WALL;
            } else {
                square = SQU_CORRIDOR;
            }

            labyrinth->squares[line][col] = square;
        }
    }

    return labyrinth;
}

// Test : game ------------------------------------------------------------------------------------

MU_TEST(test_startGame) {
    mu_check(NULL == startGame(NULL));

    Labyrinth* labyrinth = generateLabyrinth(11, 11);
    Game* game = startGame(labyrinth);

    mu_check(NULL != game);

    endGame(game);
    destroyLabyrinth(labyrinth);
}

MU_TEST(test_isGameOver) {
    mu_assert_int_eq(0, isGameOver(NULL));

    Game game;

    game.gameOver = 0;
    mu_assert_int_eq(0, isGameOver(&game));

    game.gameOver = 1;
    mu_assert_int_eq(1, isGameOver(&game));
}

MU_TEST(test_move) {
    mu_assert_int_eq(0, move(NULL, 122334534));

    Labyrinth* labyrinth = generateLabyrinthForTest(11, 11);
    labyrinth->squares[1][1] = SQU_PLAYER;

    Game* game = startGame(labyrinth);
    mu_assert_int_eq(0, move(game, 122334534));

    mu_assert_int_eq(0, move(game, DIR_LEFT));

    labyrinth->squares[1][2] = SQU_NULL;
    mu_assert_int_eq(0, move(game, DIR_RIGHT));

    labyrinth->squares[0][1] = SQU_CORRIDOR;
    mu_assert_int_eq(1, move(game, DIR_UP));

    labyrinth->squares[0][2] = SQU_DOOR;
    mu_assert_int_eq(0, move(game, DIR_RIGHT));

    labyrinth->squares[1][1] = SQU_KEY;
    mu_assert_int_eq(1, move(game, DIR_DOWN));
    mu_check(SQU_END == getSquare(labyrinth, 0, 2));

    mu_assert_int_eq(1, move(game, DIR_UP));
    
    mu_assert_int_eq(0, isGameOver(game));
    mu_assert_int_eq(1, move(game, DIR_RIGHT));
    mu_assert_int_eq(1, isGameOver(game));

    endGame(game);
    destroyLabyrinth(labyrinth);
}

MU_TEST(test_endGame) {
    endGame(NULL);

    Labyrinth* labyrinth = generateLabyrinth(11, 11);

    Game* game = startGame(labyrinth);

    mu_check(NULL != game);
    endGame(game);

    destroyLabyrinth(labyrinth);
}

// Test : labyrinth -------------------------------------------------------------------------------

MU_TEST(test_isValidSquare) {
    Labyrinth* labyrinth = generateLabyrinthForTest(5, 5);

    labyrinth->squares[2][2] = SQU_NULL;

    mu_assert_int_eq(0, isValidSquare(labyrinth, 10, 10));
    mu_assert_int_eq(1, isValidSquare(labyrinth, 2, 2));
    mu_assert_int_eq(1, isValidSquare(labyrinth, 2, 1));

    destroyLabyrinth(labyrinth);
}

MU_TEST(test_getSquare) {
    Labyrinth* labyrinth = generateLabyrinthForTest(5, 5);

    mu_check(SQU_NULL == getSquare(labyrinth, 10, 10));

    labyrinth->squares[2][2] = SQU_NULL;
    mu_check(SQU_NULL == getSquare(labyrinth, 2, 2));

    labyrinth->squares[2][2] = SQU_COIN;
    mu_check(SQU_COIN == getSquare(labyrinth, 2, 2));

    destroyLabyrinth(labyrinth);
}

MU_TEST(test_setSquare) {
    Labyrinth* labyrinth = generateLabyrinthForTest(5, 5);

    mu_assert_int_eq(0, setSquare(labyrinth, 10, 10, SQU_COIN));

    labyrinth->squares[2][2] = SQU_NULL;
    mu_assert_int_eq(1, setSquare(labyrinth, 2, 2, SQU_COIN));
    mu_check(SQU_COIN == labyrinth->squares[2][2]);

    destroyLabyrinth(labyrinth);
}

MU_TEST(test_destroyLabyrinth) {
    destroyLabyrinth(NULL);

    Labyrinth* labyrinth = generateLabyrinthForTest(11, 11);
    destroyLabyrinth(labyrinth);
}

// Test : labyrinth_generator ---------------------------------------------------------------------

MU_TEST(test_generateLabyrinth) {
    Labyrinth* labyrinth;
    
    labyrinth = generateLabyrinth(3, 3);
    mu_check(NULL == labyrinth);

    labyrinth = generateLabyrinth(5, 6);
    mu_check(NULL == labyrinth);

    labyrinth = generateLabyrinth(5, 7);
    mu_check(NULL != labyrinth);
    mu_assert_int_eq(5, labyrinth->height);
    mu_assert_int_eq(7, labyrinth->width);
    mu_check(NULL != labyrinth->squares);

    destroyLabyrinth(labyrinth);
}

// Test : labyrinth_repository --------------------------------------------------------------------

MU_TEST(test_saveAndLoadLabyrinth) {
    char* labyrinthName = "test_saveAndLoadLabyrinth";

    // Save
    Labyrinth* labyrinth = generateLabyrinth(5, 5);

    mu_assert_int_eq(0, saveLabyrinth(NULL, NULL));
    mu_assert_int_eq(0, saveLabyrinth(NULL, labyrinth));
    mu_assert_int_eq(0, saveLabyrinth(labyrinthName, NULL));
    mu_assert_int_eq(1, saveLabyrinth(labyrinthName, labyrinth));

    // Load
    Labyrinth* other = NULL;

    mu_check(NULL == loadLabyrinth(NULL));

    other = loadLabyrinth(labyrinthName);
    mu_check(NULL != other);

    mu_assert_string_eq(labyrinthName, other->name);
    mu_assert_int_eq(labyrinth->height, other->height);
    mu_assert_int_eq(labyrinth->width, other->width);
    mu_assert_int_eq(labyrinth->monsters, other->monsters);

    for (size_t line = 0; line < labyrinth->height; line++) {
        for (size_t col = 0; col < labyrinth->width; col++) {
            mu_check(labyrinth->squares[line][col] == other->squares[line][col]);
        }
    }

    destroyLabyrinth(other);
    destroyLabyrinth(labyrinth);
}

// Test : monsters --------------------------------------------------------------------------------

MU_TEST(test_addAndGetMonsters) {
    Labyrinth* labyrinth = generateLabyrinth(11, 11);

    mu_check(NULL == getMonsters(NULL));
    mu_check(NULL == getMonsters(labyrinth));

    addMonsters(labyrinth);
    Monsters* monsters = getMonsters(labyrinth);
    mu_check(NULL != monsters);

    destroyMonsters(monsters);
    destroyLabyrinth(labyrinth);
}

MU_TEST(test_isMonster) {
    int normalCount = 9;
    Square normalSquares[] = {
        SQU_CORRIDOR,
        SQU_WALL,
        SQU_COIN,
        SQU_TRAP,
        SQU_KEY,
        SQU_DOOR,
        SQU_END,
        SQU_PLAYER,
        SQU_NULL
    };

    int monsterCount = 9;
    Square monsterSquares[] = {
        SQU_OGRE,
        SQU_OGRE_IN_COIN,
        SQU_OGRE_IN_TRAP,
        SQU_OGRE_IN_KEY,
        SQU_SPECTRUM,
        SQU_SPECTRUM_IN_WALL,
        SQU_SPECTRUM_IN_COIN,
        SQU_SPECTRUM_IN_TRAP,
        SQU_SPECTRUM_IN_KEY,
    };

    Labyrinth* labyrinth = generateLabyrinthForTest(5, 5);

    Position position = {2, 2};
    mu_assert_int_eq(0, isMonster(NULL, position));

    Position wrong = {-1, -1};
    mu_assert_int_eq(0, isMonster(labyrinth, wrong));

    for (int i = 0; i < normalCount; i++) {
        labyrinth->squares[2][2] = normalSquares[i];
        mu_assert_int_eq(0, isMonster(labyrinth, position));
    }

    for (int i = 0; i < monsterCount; i++) {
        labyrinth->squares[2][2] = monsterSquares[i];
        mu_assert_int_eq(1, isMonster(labyrinth, position));
    }

    destroyLabyrinth(labyrinth);
}

MU_TEST(test_killMonster) {
    Labyrinth* labyrinth = generateLabyrinth(7, 7);
    addMonsters(labyrinth);
    Monsters* monsters = getMonsters(labyrinth);

    int count = monsters->count;
    if (count > 0) {
        Monster* monster = monsters->monsters[0];

        killMonster(monsters, monster->position);

        mu_check(count - 1 == (int) monsters->count);
        mu_check(monster != monsters->monsters[0]);
    }

    destroyMonsters(monsters);
    destroyLabyrinth(labyrinth);
}

MU_TEST(test_destroyMonsters) {
    destroyMonsters(NULL);

    Labyrinth* labyrinth = generateLabyrinth(7, 7);
    addMonsters(labyrinth);
    Monsters* monsters = getMonsters(labyrinth);

    destroyMonsters(monsters);
    destroyLabyrinth(labyrinth);
}

// Test : inputs ----------------------------------------------------------------------------------

MU_TEST(test_askForCharInList) {
    printf("START --------------------------\n");
    printf("test : test_askForCharInList\n");

    printf("Valeurs autorisées : 'a', 'b', 'c'\n");
    char values[] = {'a', 'b', 'c'};

    char c = askForCharInList(values, 3);
    printf("retour : %c\n", c);
    
    printf("END ----------------------------\n");
}

MU_TEST(test_askForIntInList) {
    printf("START --------------------------\n");
    printf("test : test_askForIntInList\n");

    printf("Valeurs autorisées : '-4', '6', '123'\n");
    int values[] = {-4, 6, 123};

    int i = askForIntInList(values, 3);
    printf("retour : %d\n", i);
    
    printf("END ----------------------------\n");
}

MU_TEST(test_askForIntInRange) {
    printf("START --------------------------\n");
    printf("test : test_askForIntInRange\n");

    printf("Valeurs autorisées : [-15 ; 10]\n");

    int i = askForIntInRange(-15, 10);
    printf("retour : %d\n", i);
    
    printf("END ----------------------------\n");
}

MU_TEST(test_askForString) {
    printf("START --------------------------\n");
    printf("test : test_askForString\n");

    printf("Chaine total de 4 caractères :\n");

    char* string = malloc(sizeof(char) * 4);

    askForString(string, 4);
    printf("retour : %s\n", string);
    
    free(string);
    printf("END ----------------------------\n");
}

MU_TEST(test_fastAskForCharInList) {
    printf("START --------------------------\n");
    printf("test : test_fastAskForCharInList\n");

    printf("Valeurs autorisées : 'd', 'e', 'f', sans appuyer sur la touche entrée.\n");
    char values[] = {'d', 'e', 'f'};

    char c = fastAskForCharInList(values, 3);
    printf("retour : %c\n", c);
    
    printf("END ----------------------------\n");
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_startGame);
    MU_RUN_TEST(test_move);
    MU_RUN_TEST(test_isGameOver);
    MU_RUN_TEST(test_endGame);

    MU_RUN_TEST(test_isValidSquare);
    MU_RUN_TEST(test_getSquare);
    MU_RUN_TEST(test_setSquare);
    MU_RUN_TEST(test_destroyLabyrinth);

    MU_RUN_TEST(test_generateLabyrinth);
    MU_RUN_TEST(test_saveAndLoadLabyrinth);

    MU_RUN_TEST(test_addAndGetMonsters);
    MU_RUN_TEST(test_isMonster);
    MU_RUN_TEST(test_killMonster);
    MU_RUN_TEST(test_destroyMonsters);

    MU_RUN_TEST(test_askForCharInList);
    MU_RUN_TEST(test_askForIntInList);
    MU_RUN_TEST(test_askForIntInRange);
    MU_RUN_TEST(test_askForString);
    MU_RUN_TEST(test_fastAskForCharInList);
}

int main(void) {
    MU_RUN_SUITE(test_suite);

    MU_REPORT();
    return MU_EXIT_CODE;
}
