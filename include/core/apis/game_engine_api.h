#ifndef GAME_ENGINE_API_H
#define GAME_ENGINE_API_H

#include <stdbool.h>
#include <stdio.h>

#include "../types/gameloop_callback.h"
#include "../engine_properties/running_state.h"
#include "../engine_properties/pause_gameloop_for_rendering.h"

#ifdef USE_SDL_1
#include "sdl1/screen_handler.h"
#include "sdl1/event_handler.h"
#include "sdl1/gameloop_handler.h"
#include "sdl1/graphic_handler.h"
#elif USE_SDL_2
#include "sdl2/screen_handler.h"
#include "sdl2/event_handler.h"
#include "sdl2/gameloop_handler.h"
#include "sdl2/graphic_handler.h"
#endif

#include "screen.h"

bool initializeGameEngine(int widthScreenPixels, int heightScreenPixels, const char *gameTitle, GameLoopCallback gameLoop)
{
    if (!initializeGraphicApi(widthScreenPixels, heightScreenPixels, gameTitle))
    {
        fprintf(stderr, "ERROR: Could not initialize graphic environment system");
        return EXIT_FAILURE;
    }

    if (!initializeGameloopThread(gameLoop))
    {
        fprintf(stderr, "ERROR: Could not initialize gameloop thread");
        closeGraphicApi();
        return EXIT_FAILURE;
    }

    return true;
}

bool runGame()
{
    loopEventHandlerApi();
}

void closeGraphicEnvironment()
{
    closeGraphicApi();
}

void closeGameEngine()
{
    setGameRunningState(false);
    waitGameloopFinish();
    closeGraphicEnvironment();
}

#endif