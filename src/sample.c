#include "../include/graphic_engine.h"
#include "../include/utils/geometry.h"
#include "../include/utils/font.h"
#include "../include/utils/color.h"

void *gameLoop(void *arg)
{
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

    return NULL;
}

int main()
{
    // 4:3 screen ratio size
    initGraphicEngine(640, 480, "Basic SDL Engine");
    initializeGameLoop(gameLoop);
    runEngine();
    clearEngine();
    return EXIT_SUCCESS;
}