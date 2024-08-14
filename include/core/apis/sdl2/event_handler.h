#ifndef EVENT_API_HANDLER_SDL_2_IMPLEMENTATION_H
#define EVENT_API_HANDLER_SDL_2_IMPLEMENTATION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <stdbool.h>

#include "graphic_environment.h"

#include "../../engine_properties/running_state.h"
#include "../../engine_properties/pause_gameloop_for_rendering.h"

#define gameDelay(delayValue) SDL_Delay(delayValue)

void loopEventHandlerApi()
{
    SDL_Event event;
    do
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                // running = false;
                isGameRunning = false;
            }
        }

        if (pauseGameLoopForRendering)
        {
            SDL_UpdateWindowSurface(gGameEngineGraphicEnvironment.window);
            resumeGameloop();
        }
    } while (isGameRunning);
}

#endif