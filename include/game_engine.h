#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "graphic_engine.h"

// gameloop must be define in the source where game is created
#define CREATE_GAME(widthScreen, heightScreen, gameTitle)        \
    int main()                                                   \
    {                                                            \
        initGraphicEngine(widthScreen, heightScreen, gameTitle); \
        initializeGameLoop(gameLoop);                            \
        runEngine();                                             \
        clearEngine();                                           \
        return EXIT_SUCCESS;                                     \
    }

#endif