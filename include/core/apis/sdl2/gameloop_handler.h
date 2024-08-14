#ifndef GAMELOOP_API_HANDLER_SDL_2_H
#define GAMELOOP_API_HANDLER_SDL_2_H

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

#include "../../types/gameloop_callback.h"
#include "../../engine_properties/running_state.h"

typedef struct _tag_gameloop_handler_
{
    SDL_Thread *gameThread;
} GameloopHandler;

static GameloopHandler gGameloopHandler;

bool initializeGameloopThread(GameLoopCallback gameLoop)
{
    SDL_Thread *gameThread = SDL_CreateThread((GameLoopCallback)gameLoop, "GameLoop", NULL);

    if (!gameThread)
    {
        fprintf(stderr, "ERROR: Could not initialize gameloop thread");
        return false;
    }

    gGameloopHandler.gameThread = gameThread;

    return true;
}

void waitGameloopFinish()
{
    setGameRunningState(false);
    SDL_WaitThread(gGameloopHandler.gameThread, NULL);
}

#endif