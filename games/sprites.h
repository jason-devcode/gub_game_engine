#ifndef GAME_SPRITES_H
#define GAME_SPRITES_H

#include "../include/utils/sprite.h"

// use a general spritesheet for all game aspect
Sprite *gBombermanSpritesheet;

bool initializeGameSprites()
{
    gBombermanSpritesheet = loadSpriteFromTextureFile("./resources/bomberman_spritesheet.bmp", 14, 24);

    if (!gBombermanSpritesheet)
        return false;

    return true;
}

void releaseGameSprites()
{
    releaseSpriteResources(gBombermanSpritesheet);
}

#endif