#ifndef GRAPHIC_API_HANDLER_SDL_2_H
#define GRAPHIC_API_HANDLER_SDL_2_H

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "graphic_environment.h"

#include "../../engine_properties/framebuffer.h"
#include "../../engine_properties/screen_dimensions.h"

bool createWindowViewport(int widthScreenPixels, int heightScreenPixels, const char *windowTitle)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "ERROR: Cannot initialize SDL 2 video subsystem: %s", SDL_GetError());
        return false;
    }

    SDL_Window *window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, widthScreenPixels, heightScreenPixels, SDL_WINDOW_SHOWN);
    if (!window)
    {
        fprintf(stderr, "ERROR: Could not create window SDL 2: %s", SDL_GetError());
        return false;
    }

    SDL_Surface *screenSurface = SDL_GetWindowSurface(window);

    if (!screenSurface)
    {
        fprintf(stderr, "Could not get window surface: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    gGameEngineGraphicEnvironment.window = window;
    gGameEngineGraphicEnvironment.screenSurface = screenSurface;

    framebuffer = (uint32_t *)screenSurface->pixels;

    gScreenWidth = widthScreenPixels;
    gCorrectPixelsWidth = screenSurface->pitch>>2;
    gScreenHeight = heightScreenPixels;

    for (int y = 0; y < heightScreenPixels; ++y)
    {
        for (int x = 0; x < widthScreenPixels; ++x)
        {
            framebuffer[y * widthScreenPixels + x] = 0; // White
        }
    }
    SDL_UpdateWindowSurface(window);

    return true;
}

bool initializeGraphicApi(int widthScreenPixels, int heightScreenPixels, const char *windowTitle)
{

    if (!createWindowViewport(widthScreenPixels, heightScreenPixels, windowTitle))
    {
        fprintf(stderr, "ERROR: Cannot create game window viewport");
        return false;
    }

    return true;
}

bool closeGraphicApi()
{
    if (gGameEngineGraphicEnvironment.window)
        SDL_DestroyWindow(gGameEngineGraphicEnvironment.window);
    gGameEngineGraphicEnvironment.window = NULL;
    SDL_Quit();
    return true;
}

#endif
