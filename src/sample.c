#include "../include/graphic_engine.h"
#include "../include/utils/geometry.h"
#include "../include/utils/font.h"
#include "../include/utils/color.h"

#include "../include/managers/event_manager.h"

void onSpaceKeyPressed()
{
    printf("deltatime: %f\n", getDeltatime());
}

void message()
{
    puts("hola");
}

void *gameLoop(void *arg)
{
    addKeyPressEventListener(SDLK_SPACE, onSpaceKeyPressed);
    addKeyReleaseEventListener(SDLK_SPACE, message);

    do
    {
        clearScreen();

        drawFormattedText(
            10, 10, 0xFFFFFF00,
            "FPS: %d\ndeltatime: %lf",
            getFps(), getDeltatime());

        drawScreen();

        renderDelay(16); // Limit to 60  FPS
    } while (ON_GAME_RUNNING);

    removeKeyPressEventListener(SDLK_SPACE, onSpaceKeyPressed);
    removeKeyReleaseEventListener(SDLK_SPACE, message);

    return NULL;
}

int main()
{
    initGraphicEngine(640, 480, "Basic SDL Engine");
    initializeGameLoop(gameLoop);
    runEngine();
    clearEngine();
    return EXIT_SUCCESS;
}