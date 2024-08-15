#include "../include/graphic_engine.h"
#include "../include/utils/geometry.h"
#include "../include/utils/font.h"
#include "../include/utils/color.h"

typedef struct
{
    float x, y;
} vec2f;

void drawRadar(vec2f *radarPosition, vec2f *playerPosition, int radarSize, float playerAngle)
{

    drawCircle(radarPosition->x, radarPosition->y, radarSize, 2, RGB(255, 0, 0));
    drawFormattedText((int)radarPosition->x - radarSize + (radarSize / 3), ((int)radarPosition->y + radarSize) + 8, 0xFFFFFFFF, "X: %.02f, Y: %.02f", playerPosition->x, playerPosition->y);
}

int gameLoop(void *arg)
{
    int radarSize = gScreenHeight >> 3;

    vec2f radarPosition = {radarSize + 100, radarSize + 100};
    vec2f playerPosition = {0, 0};

    float playerAngle = 0.0f;
    long result = 0;

    do
    {
        clearScreen();

        drawRadar(&radarPosition, &playerPosition, radarSize, playerAngle);

        drawFormattedText(
            10, 10, 0xFFFFFF00,
            "FPS: %d\ndeltatime: %lf",
            getFps(), getDeltatime());

        drawScreen();

        // renderDelay(16);
    } while (isGameRunning);

    return EXIT_SUCCESS;
}

int main()
{
    // 16:9 screen ratio size
    // initGraphicEngine(1280 >> 2, 720 >> 3, "Basic SDL Engine");
    initGraphicEngine(640, 480, "Basic SDL Engine");
    initializeGameLoop(gameLoop);
    runEngine();
    clearEngine();
    return EXIT_SUCCESS;
}