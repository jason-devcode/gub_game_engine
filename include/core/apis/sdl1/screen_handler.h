#ifndef SCREEN_API_HANDLER_SDL_1_H
#define SCREEN_API_HANDLER_SDL_1_H

#include <SDL/SDL.h>

#include "../../engine_properties/running_state.h"
#include "timers_handler.h"
#include "graphic_environment.h"

/**
 * @brief Updates the screen with the current framebuffer contents.
 * 
 * This macro calls `SDL_Flip` to update the display with the contents of the
 * framebuffer using SDL 1.2. It also updates the timers to maintain timing consistency.
 */
#define drawScreen()                                       \
    SDL_Flip(gGameEngineGraphicEnvironment.screenSurface); \
    updateTimers();

#endif