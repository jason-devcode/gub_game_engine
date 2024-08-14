#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "apis/game_engine_api.h"

#define CREATE_GAME(widthScreen, heightScreen, gameTitle)                     \
    int main()                                                                \
    {                                                                         \
        initializeGameEngine(widthScreen, heightScreen, gameTitle, gameLoop); \
        runGame();                                                            \
        closeGameEngine();                                                    \
        return EXIT_SUCCESS;                                                  \
    }

#endif