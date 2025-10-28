// TODO : tests
// TODO : structuration de fichiers (static)
// TODO : labyrinth destroy

// TODO : labyrinth height width et size_t
// TODO : indentation vscode
// TODO : todo dans le code
// TODO : limites

utiliser valgrind
copier config debbuger

labyrinth -> matrice + enum





void createLabyrinth() {
    size_t height;
    size_t width;
    char name[LABYRINTH_NAME_LENGHT];

    displayLabyrinthCreationForm(&height, &width, &name);

    Labyrinth labyrinth = generateLabyrinth(height, width);

    saveLabyrinth(name, labyrinth);

    destroyLabyrinth(labyrinth);
}






static void clearInterface();


static void clearInterface() {
    system("clear");
}


Action getAction(const MenuData* menu) {
    clearInterface();

    printf("1. Créer un labyrinthe\n");
    printf("2. Charger un labyrinthe\n");
    if (menu->LabyrinthLoaded) {
        printf("3. Jouer");
    }
    printf("4. Quitter");

    int choice = (menu->LabyrinthLoaded)
        ? askForIntInList([1, 2, 3, 4], 4)
        : askForIntInList([1, 2, 4], 3);
    
    switch (choice) {
        case 1: return ACT_CREATE;
        case 2: return ACT_LOAD;
        case 3: return ACT_PLAY;
        default: return ACT_QUIT;
    }
}




Direction getDirection();

void displayLabyrinth(const Labyrinth* labyrinth) {
    for (size_t line = 0; line < labyrinth->height; line++) {
        for (size_t col = 0; col < labyrinth->width; col++) {
            printf("%c ", labyrinth->squares[line][col]);
        }
        printf("\n");
    }
}






void play(Labyrinth* labyrinth);
Labyrinth* load(unsigned int id);

Labyrinth* load(unsigned int id) {
    char* fileName = getFileName(id);
    Labyrinth labyrinth;
    
    return (loadLabyrinth(fileName, &labyrinth))
        ? &labyrinth
        : NULL;
}

int save(unsigned int id, const Labyrinth* labyrinth) {
    char* fileName = getFileName(id);

    return saveLabyrinth(fileName, labyrinth);
}

void play(Labyrinth* labyrinth) {
    Game* game = startGame(labyrinth);

    while(!isGameOver(game)) {
        displayLabyrinth(labyrinth); // TODO : Display Game ??

        Direction direction;
        do {
            direction = getDirection();
        } while (!move(game, direction));
    }

    destroyGame(game);
}

Labyrinth* create();
Labyrinth* load();

int main(void) {
    Labyrinth* labyrinth = NULL;
    MenuData menu;
    
    Action action;
    do {
        menu.LabyrinthLoaded = labyrinth == NULL
            ? 0
            : 1;

        action = getAction(&menu);

        switch (action) {
            case ACT_CREATE:
                labyrinth = create();

                break;
            case ACT_LOAD:
                labyrinth = load();

                break;

            case ACT_PLAY:
                if (labyrinth != NULL) {
                    play(labyrinth);
                }

                break;
        }
    } while (action != ACT_QUIT);

    return 0;
}


