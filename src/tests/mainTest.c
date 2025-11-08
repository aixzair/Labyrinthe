#include <stdio.h>

#include "./../../ressources/minunit.h"


#include "game.h"
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

MU_TEST(test_endGame) {
    endGame(NULL);
}

// Test : labyrinth -------------------------------------------------------------------------------

MU_TEST(test_isValidSquare) {
    Labyrinth* labyrinth = generateLabyrinthForTest(5, 5);

    labyrinth->squares[2][2] = SQU_NULL;

    mu_assert_int_eq(0, isValidSquare(labyrinth, 10, 10));
    mu_assert_int_eq(0, isValidSquare(labyrinth, 2, 2));
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

    mu_assert_int_eq(1, setSquare(labyrinth, 10, 10, SQU_COIN));

    labyrinth->squares[2][2] = SQU_NULL;
    mu_assert_int_eq(1, setSquare(labyrinth, 2, 2, SQU_COIN));
    mu_check(SQU_COIN == labyrinth->squares[2][2]);

    destroyLabyrinth(labyrinth);
}

MU_TEST(test_destroyLabyrinth) {
    destroyLabyrinth(NULL);

    Labyrinth* labyrinth = generateLabyrinthForTest(5, 5);
    destroyLabyrinth(labyrinth);

    mu_check(NULL == labyrinth);
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
    char labyrinthName = "test_saveAndLoadLabyrinth";

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
    destroyLabyrinth(labyrinthName);
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

// TODO : getMonsters
// TODO : isMonster
// TODO : killMonster
// TODO : destroyMonsters

// Test : inputs ----------------------------------------------------------------------------------
// TODO : askForCharInList
// TODO : askForIntInList
// TODO : askForIntInRange
// TODO : askForString
// TODO : fastAskForCharInList

MU_TEST(test_free_resets_state) {
    /*struct matrix_t m;

    m = alloc_matrix(3u, 4u);
    init_matrix(&m, DOT_KEY);
    free_matrix(&m);
    mu_assert_int_eq(0, (int)m.rows);
    mu_assert_int_eq(0, (int)m.columns);
    mu_check(m.data == NULL);

    free_matrix(&m);
    mu_assert_int_eq(0, (int)m.rows);
    mu_assert_int_eq(0, (int)m.columns);
    mu_check(m.data == NULL);*/
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_startGame);
    MU_RUN_TEST(test_isGameOver);
    MU_RUN_TEST(test_endGame);

    MU_RUN_TEST(test_isValidSquare);
    MU_RUN_TEST(test_getSquare);
    MU_RUN_TEST(test_setSquare);
    MU_RUN_TEST(test_destroyLabyrinth);

    MU_RUN_TEST(test_generateLabyrinth);
    MU_RUN_TEST(test_saveAndLoadLabyrinth);
}

int main(void) {
    MU_RUN_SUITE(test_suite);

    MU_REPORT();
    return MU_EXIT_CODE;
}
