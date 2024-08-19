#include "../include/gub.h"

#include "../include/utils/texture.h"

void gameLoop()
{
    Texture *sampleTexture = loadTextureFromImageFile("./temp/test.bmp");

    do
    {
        clearScreen();
#define CUSTOM_WIDTH 256
#define CUSTOM_HEIGHT 256

        // drawTexture(GET_MOUSE_X() - (sampleTexture->width >> 1), GET_MOUSE_Y() - (sampleTexture->height >> 1), sampleTexture);
        drawTextureScaled(GET_MOUSE_X() - (CUSTOM_WIDTH >> 1), GET_MOUSE_Y() - (CUSTOM_HEIGHT >> 1), sampleTexture, CUSTOM_WIDTH, CUSTOM_HEIGHT);
        // drawTexture(GET_MOUSE_X() - (sampleTexture->width >> 1), GET_MOUSE_Y() - (sampleTexture->height >> 1), sampleTexture);

        drawScreen();
        renderDelay(16);
    } while (isGameRunning);

    releaseTextureResources(sampleTexture);
}

CREATE_GAME(640, 640, "SAMPLE TEXTURE")