#ifndef SCREEN_API_HANDLER_SDL_2_H
#define SCREEN_API_HANDLER_SDL_2_H

#include "timers_handler.h"
#include "../../engine_properties/running_state.h"
#include "../../engine_properties/pause_gameloop_for_rendering.h"

#include <SDL2/SDL.h>

/**
 * @brief Pauses the game loop and updates the window surface.
 *
 * In SDL2, this function sets a global variable to allow the window surface to be updated
 * in the main loop. This is necessary because updating the window surface cannot be performed
 * from threads other than the main process thread.
 *
 * The function pauses the game loop, waits until the rendering process is completed, and
 * then resumes the game loop. During the pause, it updates the timers to ensure timing
 * consistency.
 */
static inline void drawScreen()
{
    pauseGameloop();
    do
    {
        SDL_Delay(0);
    } while (pauseGameLoopForRendering && isGameRunning); // loop to pause the game loop while updating the window surface
    updateTimers();
}

#endif