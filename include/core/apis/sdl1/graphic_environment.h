#ifndef GRAPHIC_ENVIRONMENT_PROPERTIES_SDL1_H
#define GRAPHIC_ENVIRONMENT_PROPERTIES_SDL1_H

#include <SDL/SDL.h>

/**
 * @brief Structure that defines the properties of the graphic environment.
 *
 * This structure holds information about the graphic environment used
 * by the game engine. In SDL 1.2, it includes a pointer to the screen surface.
 */
typedef struct _tag_graphic_environment_properties_
{
    /**
     * @brief Pointer to the screen surface.
     *
     * This member holds the SDL surface that represents the screen. It is used
     * for rendering the graphics in the SDL 1.2 environment.
     */
    SDL_Surface *screenSurface;
} GraphicEnvironment;

/**
 * @brief Global instance of the graphic environment.
 *
 * This global instance represents the current graphic environment settings
 * and state for the game engine. It includes information such as the screen surface.
 */
GraphicEnvironment gGameEngineGraphicEnvironment;

#endif