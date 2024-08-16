#ifndef GAMELOOP_API_HANDLER_SDL_2_H
#define GAMELOOP_API_HANDLER_SDL_2_H

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

#include "../../types/gameloop_callback.h"
#include "../../engine_properties/running_state.h"

/**
 * @struct GameloopHandler
 * @brief Structure to manage the game loop thread.
 *
 * This structure holds the SDL thread handle for the game loop, allowing
 * initialization and management of the thread responsible for running the game loop.
 */
typedef struct _tag_gameloop_handler_
{
    SDL_Thread *gameThread; /**< SDL thread handle for the game loop. */
} GameloopHandler;

/** Static instance of the GameloopHandler. */
static GameloopHandler gGameloopHandler;

/**
 * @brief Initializes the game loop thread.
 *
 * Creates and starts a new SDL thread to run the provided game loop callback function.
 *
 * @param gameLoop The callback function to be run in the game loop thread.
 * @return True if the thread was successfully created; otherwise, false.
 */
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

/**
 * @brief Waits for the game loop thread to finish execution.
 *
 * Sets the game running state to false, signaling the game loop to stop, and
 * then waits for the game loop thread to finish its execution.
 */
void waitGameloopFinish()
{
    setGameRunningState(false);
    SDL_WaitThread(gGameloopHandler.gameThread, NULL);
}

#endif