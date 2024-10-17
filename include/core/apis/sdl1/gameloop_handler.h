#ifndef GAMELOOP_API_HANDLER_SDL_2_H
#define GAMELOOP_API_HANDLER_SDL_2_H

#include <stdio.h>
#include <stdbool.h>

#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>

#include "../../types/gameloop_callback.h"
#include "../../engine_properties/running_state.h"

/**
 * @brief Structure to manage the game loop thread.
 *
 * This structure holds the SDL thread handle used for running the game loop.
 */
typedef struct _tag_gameloop_handler_
{
    /**
     * @brief SDL thread handle for the game loop.
     *
     * This member holds the SDL thread handle used to run the game loop in a separate thread.
     */
    SDL_Thread *gameThread;
} GameloopHandler;

/**
 * @brief Global instance of the game loop handler.
 *
 * This global instance manages the game loop thread within the application.
 */
static GameloopHandler gGameloopHandler;

/**
 * @brief Initializes and starts the game loop thread.
 *
 * This function creates and starts a new SDL thread to run the game loop.
 *
 * @param gameLoop The callback function that represents the game loop.
 * @return true if the game loop thread is successfully created; false otherwise.
 */
bool initializeGameloopThread(GameLoopCallback gameLoop)
{
    SDL_Thread *gameThread = SDL_CreateThread((GameLoopCallback)gameLoop, NULL);

    if (!gameThread)
    {
        fprintf(stderr, "ERROR: Could not initialize gameloop thread\n");
        return false;
    }

    gGameloopHandler.gameThread = gameThread;

    return true;
}

/**
 * @brief Waits for the game loop thread to finish.
 *
 * This function signals the game loop to stop running, then waits for the
 * game loop thread to complete its execution.
 */
void waitGameloopFinish()
{
    setGameRunningState(false);
    SDL_WaitThread(gGameloopHandler.gameThread, NULL);
}

#endif