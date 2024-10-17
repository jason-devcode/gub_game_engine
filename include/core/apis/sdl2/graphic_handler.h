#ifndef GRAPHIC_API_HANDLER_SDL_2_H
#define GRAPHIC_API_HANDLER_SDL_2_H

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "graphic_environment.h"

#include "../../engine_properties/framebuffer.h"
#include "../../engine_properties/depthbuffer.h"
#include "../../engine_properties/screen_dimensions.h"

/**
 * @brief Creates a window and initializes the viewport for SDL2 graphics.
 *
 * This function initializes SDL2's video subsystem, creates an SDL window with
 * the specified dimensions and title, and obtains the surface for rendering.
 * It also initializes the framebuffer and sets it to white.
 *
 * @param widthScreenPixels The width of the window in pixels.
 * @param heightScreenPixels The height of the window in pixels.
 * @param windowTitle The title of the window.
 *
 * @return true if the window and surface are successfully created, false otherwise.
 */
bool createWindowViewport(int widthScreenPixels, int heightScreenPixels, const char *windowTitle)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "ERROR: Could not initialize SDL 2 video subsystem: %s", SDL_GetError());
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

    gScreenWidth = widthScreenPixels;
    gCorrectPixelsWidth = screenSurface->pitch >> 2;
    gScreenHeight = heightScreenPixels;

    framebuffer = (uint32_t *)screenSurface->pixels;

    // Allocate memory for the depth buffer
    depthbuffer = (double *)malloc(sizeof(double[gScreenWidth * gScreenHeight]));

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

/**
 * @brief Initializes the SDL2 graphics API and creates the window viewport.
 *
 * This function calls `createWindowViewport` to set up the window and surface.
 *
 * @param widthScreenPixels The width of the window in pixels.
 * @param heightScreenPixels The height of the window in pixels.
 * @param windowTitle The title of the window.
 *
 * @return true if initialization is successful, false otherwise.
 */
bool initializeGraphicApi(int widthScreenPixels, int heightScreenPixels, const char *windowTitle)
{

    if (!createWindowViewport(widthScreenPixels, heightScreenPixels, windowTitle))
    {
        fprintf(stderr, "ERROR: Could not create game window viewport");
        return false;
    }

    return true;
}

/**
 * @brief Closes the SDL2 graphics API and destroys the window.
 *
 * This function cleans up the SDL2 resources and closes the window.
 *
 * @return true if the cleanup is successful, false otherwise.
 */
bool closeGraphicApi()
{
    if (gGameEngineGraphicEnvironment.window)
        SDL_DestroyWindow(gGameEngineGraphicEnvironment.window);
    gGameEngineGraphicEnvironment.window = NULL;
    if (depthbuffer)
        free(depthbuffer);
    SDL_Quit();
    return true;
}

#endif
