#ifndef SCREEN_API_HANDLER_SDL_2_H
#define SCREEN_API_HANDLER_SDL_2_H

#include "../../engine_properties/running_state.h"
#include "../../engine_properties/pause_gameloop_for_rendering.h"

#include <SDL2/SDL.h>

void drawScreen()
{
    pauseGameloop();
    do
    {
        SDL_Delay(0);
    } while (pauseGameLoopForRendering && isGameRunning);
}

#endif