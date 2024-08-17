#ifndef RUNNING_STATE_ENGINE_PROP_H
#define RUNNING_STATE_ENGINE_PROP_H

#include <stdbool.h>

// use for gameloop condition
bool isGameRunning = true;

#define setGameRunningState(state) \
    do                             \
    {                              \
        isGameRunning = state;     \
    } while (false);

#define getGameRunningState() (isGameRunning)

#endif