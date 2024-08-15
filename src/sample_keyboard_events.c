#include "../include/gub.h"
#include "../include/utils/keyboard.h"

void pressKeyA()
{
    puts("KEY A PRESSED");
}

int gameLoop(void *args)
{
    addKeyPressEventListener(SDLK_a, pressKeyA);
    do
    {
        clearScreen();
        drawScreen();
    } while (isGameRunning);

    return EXIT_SUCCESS;
}

CREATE_GAME(512, 512, "SAMPLE KEYBOARD EVENTS")