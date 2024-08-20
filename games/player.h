#ifndef PLAYER_H
#define PLAYER_H

#include "entities.h"

void initializePlayerProperties()
{
    player->speed = 15;
    player->position = (Vec2f){gHalfScreenWidth, gHalfScreenHeight};
}

void initializePlayer()
{
    initializePlayerProperties();
}

#endif