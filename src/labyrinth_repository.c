#include "labyrinth.h"

#include <stdio.h>
#include <string.h>

#define PATH_LABYRINTH "labyrinths"
#define FILE_PATH_LENGTH 200

static char* getFilePath(const char* fileName);

static char* getFilePath(const char* fileName) {
    char* filePath = malloc(sizeof(char) * FILE_PATH_LENGTH);
    if (filePath == NULL) {
        return NULL;
    }

    if (sprintf(filePath, PATH_LABYRINTH "/%s.cfg", fileName) < 0) {
        free(filePath);

        return NULL;
    }

    return filePath;
}

int getLabyrinthsNames(char** names, int namesLength, int stringLength) {
    FILE* file = popen("ls -p " PATH_LABYRINTH " | grep -v / | grep '\\.cfg$' | sed 's/\\.cfg$//'", "r");
    if (file == NULL) {
        return -1;
    }

    int count = 0;
    while (fgets(names[count], stringLength * sizeof(char), file) != NULL) {
        if (count == namesLength) {
            break;
        }

        if (strchr(names[count], '\n') != NULL) {
            names[count][strcspn(names[count], "\n")] = '\0';
        }

        names[count][stringLength - 1] = '\0';
        count++;
    }

    pclose(file);
    return count;
}

Labyrinth* loadLabyrinth(char* fileName) {
    Labyrinth* labyrinth = malloc(sizeof(Labyrinth));
    labyrinth->name = malloc(strlen(fileName) + 1);
    strcpy(labyrinth->name, fileName);

    char* path = getFilePath(fileName);
    if (path == NULL) {
        return 0;
    }

    FILE* file = fopen(path, "rb");
    free(path);

    if (file == NULL) {
        free(labyrinth);
        return NULL;
    }

    fread(&labyrinth->height, sizeof(size_t), 1, file);
    fread(&labyrinth->width, sizeof(size_t), 1, file);

    labyrinth->squares = malloc(sizeof(Square*) * labyrinth->height);
    for (size_t line = 0; line < labyrinth->height; line++) {
        labyrinth->squares[line] = malloc(sizeof(Square) * labyrinth->width);
    }

    for (size_t line = 0; line < labyrinth->height; line++) {
        fread(labyrinth->squares[line], sizeof(Square), labyrinth->width, file);
    }

    fclose(file);
    return labyrinth;
}

int saveLabyrinth(const char* fileName, const Labyrinth* labyrinth) {
    char* path = getFilePath(fileName);
    if (path == NULL) {
        return 0;
    }

    FILE* file = fopen(path, "wb");
    free(path);

    if (file == NULL) {
        return 0;
    }

    fwrite(&labyrinth->height, sizeof(size_t), 1, file);
    fwrite(&labyrinth->width, sizeof(size_t), 1, file);

    for (size_t line = 0; line < labyrinth->height; line++) {
        fwrite(labyrinth->squares[line], sizeof(Square), labyrinth->width, file);
    }

    fclose(file);
    return 1;
}
