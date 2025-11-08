#include "game.h"

#include "labyrinth.h"

// Defines ----------------------------------------------------------------------------------------

#define TRAP_MALUS 10
#define TURN_MALUS 1
#define MONSTER_MALUS 30
#define COIN_BONUS 20

// Implémentations --------------------------------------------------------------------------------

Game* startGame(Labyrinth* labyrinth) {
    Game* game = malloc(sizeof(Game));

    game->gameOver = 0;
    game->score = (int) (labyrinth->height * labyrinth->width / 4);
    game->playerPosition.x = 0;
    game->playerPosition.y = 0;
    game->labyrinth = labyrinth;

    if (labyrinth->monsters) {
        game->monsters = getMonsters(labyrinth);
    } else {
        game->monsters = NULL;
    }

    for (size_t line = 0; line < labyrinth->height; line++) {
        for (size_t col = 0; col < labyrinth->width; col++) {
            if (labyrinth->squares[line][col] == SQU_PLAYER) {
                game->playerPosition.x = col;
                game->playerPosition.y = line;
            }
        }
    }

    return game;
}

int move(Game* game, Direction direction) {
    if (game == NULL || game->labyrinth == NULL) {
        return 0;
    }

    if (isGameOver(game)) {
        return 0;
    }

    // Récupère la nouvelle psosition
    Position newPosition;
    switch (direction) {
        case DIR_UP:
            newPosition.y = game->playerPosition.y - 1;
            newPosition.x = game->playerPosition.x;
            break;
        case DIR_DOWN:
            newPosition.y = game->playerPosition.y + 1;
            newPosition.x = game->playerPosition.x;
            break;
        case DIR_RIGHT:
            newPosition.y = game->playerPosition.y;
            newPosition.x = game->playerPosition.x + 1;
            break;
        case DIR_LEFT:
            newPosition.y = game->playerPosition.y;
            newPosition.x = game->playerPosition.x - 1;
            break;
        default:
            return 0;
    }

    if (!isValidSquare(game->labyrinth, newPosition.y, newPosition.x)) {
        return 0;
    }

    char square = getSquare(game->labyrinth, newPosition.y, newPosition.x);
    switch (square) {
        case SQU_NULL:
        case SQU_DOOR:
        case SQU_WALL:
        case SQU_SPECTRUM_IN_WALL:
            return 0;
    }

    // Met à jour le score
    // NOTE : Le joueur bouge forcément
    if (game->monsters) {
        moveMonsters(game->labyrinth, game->monsters);
    }

    switch (square) {
        case SQU_CORRIDOR:
            break;
        case SQU_END:
            game->gameOver = 1;
            break;
        case SQU_COIN:
            game->score += COIN_BONUS;
            break;
        case SQU_TRAP:
            game->score -= TRAP_MALUS;
            break;
        case SQU_KEY:
        case SQU_SPECTRUM_IN_KEY:
        case SQU_OGRE_IN_KEY:
            for (size_t line = 0; line < game->labyrinth->height; line++) {
                for (size_t col = 0; col < game->labyrinth->width; col++) {
                    if (getSquare(game->labyrinth, line, col) == SQU_DOOR) {
                        setSquare(game->labyrinth, line, col, SQU_END);
                    }
                }
            }
            break;
    }

    if (isMonster(game->labyrinth, newPosition)) {
        killMonster(game->monsters, newPosition);
        game->score -= MONSTER_MALUS;
    }

    game->score -= TURN_MALUS;

    // Déplace le joueur
    setSquare(game->labyrinth, game->playerPosition.y, game->playerPosition.x, SQU_CORRIDOR);
    game->playerPosition = newPosition;
    setSquare(game->labyrinth, game->playerPosition.y, game->playerPosition.x, SQU_PLAYER);

    return 1;
}

int isGameOver(Game* game) {
    return game->gameOver;
}

void endGame(Game* game){
    if (game->monsters != NULL) {
        destroyMonsters(game->monsters);
    }
    free(game);
}
