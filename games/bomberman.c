#include "../include/gub.h"

#include "sprites.h"
#include "animations.h"
#include "player.h"
#include "enemies.h"
#include "events.h"

bool initializeGame()
{
    setClearScreenColor(0x388700);
    initializeGameSprites();
    initializePlayer();
    initializeAnimations();
    initializeGameEvents();

    createEnemy(100, 100, 10, ENEMY_BALLON);
    createEnemy(200, 100, 10, ENEMY_ONIL);
    createEnemy(100, 200, 10, ENEMY_DALL);
    createEnemy(100, 300, 10, ENEMY_KONDORIA);
    createEnemy(100, 400, 10, ENEMY_PONTAN);
}

void releaseGame()
{
    releaseAnimations();
    releaseGameSprites();
}

void updateScene()
{
    updateEntities();
}

void renderScene()
{
    renderEntities();
}

void gameLoop()
{
    initializeGame();

    do
    {
        clearScreen();
        updateScene();
        renderScene();
        drawScreen();
        renderDelay(16);
    } while (isGameRunning);

    releaseGame();
}

CREATE_GAME(640, 700, "BOMBERMAN GAME FANMADE")