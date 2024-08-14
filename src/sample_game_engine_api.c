#include "../include/gub.h"

int gameLoop(void *args)
{
    setClearScreenColor(0xFFFF0000);
    static int i = 0;
    do
    {
        clearScreen();
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                framebuffer[i * gCorrectPixelsWidth + j] = 0xFFFF00FF;
            }
        }
        drawScreen();
    } while (isGameRunning);

    return EXIT_SUCCESS;
}

CREATE_GAME(640, 480, "SAMPLE GAME")