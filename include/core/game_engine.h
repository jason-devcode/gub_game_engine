#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "../utils/geometry.h"
#include "apis/game_engine_api.h"
#include "types/gameloop_callback.h"

#define CREATE_GAME(widthScreen, heightScreen, gameTitle)                                       \
    int main()                                                                                  \
    {                                                                                           \
        initializeGameEngine(widthScreen, heightScreen, gameTitle, (GameLoopCallback)gameLoop); \
        initializeGeometryProps();                                                              \
        runGame();                                                                              \
        closeGameEngine();                                                                      \
        return EXIT_SUCCESS;                                                                    \
    }

#endif