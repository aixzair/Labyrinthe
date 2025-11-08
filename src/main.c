#include "menu.h"
#include "user_interface.h"

int main(void) {
    Menu* menu = createMenu();

    Action action;
    do {
        action = displayMenu(menu);

        switch (action) {
            case ACT_CREATE:
                createLabyrinthAction(menu);
                break;
            case ACT_LOAD:
                loadLabyrinthAction(menu);
                break;
            case ACT_PLAY:
                playGameAction(menu);
                break;
            case ACT_SCORE:
                showScoresAction(menu);
            default:
                break;
        }
    } while (action != ACT_QUIT);

    destroyMenu(menu);

    return 0;
}
