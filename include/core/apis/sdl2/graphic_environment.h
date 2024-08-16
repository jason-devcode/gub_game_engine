#ifndef GRAPHIC_ENVIRONMENT_PROPERTIES_SDL2_H
#define GRAPHIC_ENVIRONMENT_PROPERTIES_SDL2_H

#include <SDL2/SDL.h>

/**
 * @struct GraphicEnvironment
 * @brief Structure to store graphic environment properties for SDL2.
 *
 * This structure holds pointers to the SDL window and surface used for rendering,
 * encapsulating the essential graphics-related properties needed for SDL2-based graphics
 * management.
 */
typedef struct _tag_graphic_environment_properties_
{
    SDL_Window *window;         /**< Pointer to the SDL window used for rendering. */
    SDL_Surface *screenSurface; /**< Pointer to the SDL surface for the window's framebuffer. */
} GraphicEnvironment;

/** Static instance of GraphicEnvironment for use throughout the application. */
static GraphicEnvironment gGameEngineGraphicEnvironment;

#endif