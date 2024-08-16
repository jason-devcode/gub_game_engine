#ifndef GAMELOOP_API_HANDLER_SAMPLE_IMPLEMENTATION_H
#define GAMELOOP_API_HANDLER_SAMPLE_IMPLEMENTATION_H

#include <stdbool.h>
#include "../../types/gameloop_callback.h"

/**
 * @brief Structure that defines the game loop handler.
 *
 * This structure is used to manage the game loop within the application.
 */
typedef struct _tag_gameloop_handler_
{
    /**
     * @brief The callback function that represents the game loop.
     */
    GameLoopCallback gameLoop;
} GameloopHandler;

/**
 * @brief Global instance of the game loop handler.
 *
 * This is the global instance of the game loop handler, which controls the
 * execution and state of the game loop.
 */
static GameloopHandler gGameloopHandler;

/**
 * @brief Initializes the game loop thread.
 *
 * @param gameLoop The callback function that will be executed in the game loop.
 * @return true if the game loop thread is successfully initialized.
 * @return false if the initialization fails (not implemented in this sample).
 */
bool initializeGameloopThread(GameLoopCallback gameLoop) { return true; }

/**
 * @brief Waits for the game loop to finish.
 *
 * This function blocks until the game loop has finished executing.
 */
void waitGameloopFinish() {}

#endif