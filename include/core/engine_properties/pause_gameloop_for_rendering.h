#ifndef PAUSE_GAMELOOP_FOR_RENDERING
#define PAUSE_GAMELOOP_FOR_RENDERING

#include <stdbool.h>

/**
 * This flag is used to pause the game loop when the rendering must be handled
 * by the main thread or process, rather than the game loop thread.
 *
 * Applicable in cases where the window screen surface cannot be updated from the game loop thread.
 *
 * Used in: SDL 2, WinAPI
 */

bool pauseGameLoopForRendering = false;

/**
 * Macro to pause the game loop.
 * Sets the pauseGameLoopForRendering flag to true, indicating that the game loop should pause.
 */
#define pauseGameloop() (pauseGameLoopForRendering = true)

/**
 * Macro to resume the game loop.
 * Sets the pauseGameLoopForRendering flag to false, allowing the game loop to continue.
 */
#define resumeGameloop() (pauseGameLoopForRendering = false)

#endif
