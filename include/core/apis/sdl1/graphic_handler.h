#ifndef GRAPHIC_API_HANDLER_SDL_1_2_IMPLEMENTATION_H
#define GRAPHIC_API_HANDLER_SDL_1_2_IMPLEMENTATION_H

#include <stdbool.h> // For boolean type and constants
#include <stdint.h>  // For fixed-width integer types
#include <SDL/SDL.h> // For SDL graphics functions

#include "graphic_environment.h"

#include "../../engine_properties/framebuffer.h"
#include "../../engine_properties/depthbuffer.h"
#include "../../engine_properties/screen_dimensions.h" // For screen dimensions engine properties

/**
 * Sets the window title for the SDL window.
 *
 * @param title The title to be displayed in the window’s title bar.
 */
void setWindowTitle(const char *title)
{
    SDL_WM_SetCaption(title, NULL); // Set the window title, with no icon text
}

/**
 * Initializes SDL and the graphics engine with the specified screen dimensions and window title.
 *
 * @param screenWidth Width of the screen in pixels.
 * @param screenHeight Height of the screen in pixels.
 * @param windowTitle The title of the SDL window.
 */
bool initializeGraphicApi(int widthScreenPixels, int heightScreenPixels, const char *windowTitle)
{
    // Initialize SDL video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        // Print an error message if SDL initialization fails
        fprintf(stderr, "Cannot initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Initialize Key Event Manager
    // if (!initializeEventManager(&gKeyPressEventManager, MAX_KEY_LISTENER_LISTS_COUNT))
    // {
    //     fputs("ERROR: Cannot initialize key press event manager", stderr);
    //     exit(EXIT_FAILURE);
    // }

    // if (!initializeEventManager(&gKeyReleaseEventManager, MAX_KEY_LISTENER_LISTS_COUNT))
    // {
    //     fputs("ERROR: Cannot initialize key release event manager", stderr);
    //     exit(EXIT_FAILURE);
    // }

    // if (!initializeEventManager(&gMouseEventManager, MOUSE_LAST))
    // {
    //     fputs("ERROR: Cannot initialize mouse event manager", stderr);
    //     exit(EXIT_FAILURE);
    // }

    SDL_Surface *screen = SDL_SetVideoMode(widthScreenPixels, heightScreenPixels, 32, SDL_SWSURFACE);

    if (screen == NULL)
    {
        // Print an error message if screen initialization fails
        fprintf(stderr, "Cannot set video mode: %s\n", SDL_GetError());
        return false;
    }

    gGameEngineGraphicEnvironment.screenSurface = screen;

    gScreenWidth = widthScreenPixels;
    gScreenHeight = heightScreenPixels;

    // Correct the pixel width calculation based on screen pitch
    gCorrectPixelsWidth = screen->pitch >> 2; // >> 2 is equivalent to / 4

    gScreenTotalPixels = gCorrectPixelsWidth * heightScreenPixels;

    // Set framebuffer pointer to the screen’s pixel data
    framebuffer = (uint32_t *)screen->pixels;

    // Allocate memory for the depth buffer
    depthbuffer = (double *)malloc(sizeof(double[gScreenWidth * gScreenHeight]));

    // Set the window title
    setWindowTitle(windowTitle);

    return true;
}

/**
 * Cleans up and shuts down the graphics engine.
 */
void closeGraphicApi()
{
    // clearKeyboardManagers();
    // clearGameLoopThread(); // Clean up the game loop thread
    SDL_Quit();            // Shut down SDL
    exit(EXIT_SUCCESS);
}

#endif