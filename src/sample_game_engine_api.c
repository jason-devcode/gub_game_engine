#include "../include/gub.h"
#include "../include/utils/pixel.h"
#include "../include/utils/geometry.h"

int gameLoop(void *args)
{
    // setClearScreenColor(0xFFFF0000);
    static int i = 0;
    do
    {
        clearScreen();

        // drawTriangleWire(100, 200, 300, 100, 150, 400, 0xFFFFFF00);
        drawFilledTriangleGradient(100, 200, 300, 100, 150, 400, 0xFFFFFF00, 0xFFFF0000, 0xFFFFFFFF);

        drawScreen();
    } while (isGameRunning);

    return EXIT_SUCCESS;
}

CREATE_GAME(640, 480, "SAMPLE GAME")