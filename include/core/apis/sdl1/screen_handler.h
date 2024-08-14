#ifndef SCREEN_API_HANDLER_SDL_1_H
#define SCREEN_API_HANDLER_SDL_1_H

#include <SDL/SDL.h>

#include "../../engine_properties/running_state.h"
#include "graphic_environment.h"

/**
 * Macro to update the screen with the current framebuffer contents.
 */
#define drawScreen()                                       \
    SDL_Flip(gGameEngineGraphicEnvironment.screenSurface); \
    // UPDATE_TIMERS()

#endif