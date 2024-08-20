#ifndef ENEMIES_H
#define ENEMIES_H

#include "entities.h"
#include "animations.h"
#include "sprites.h"

bool allocateEnemy()
{
    if (freeEntitySlot >= MAX_GAME_ENTITIES)
        return false; // cannot create more entities
    enemySlotFree = &entities[freeEntitySlot];
    ++freeEntitySlot;
    return true;
}

void initializeEnemyProperties(int posX, int posY, int speed, int type)
{
    entities[numEntities].speed = speed;
    entities[numEntities].position = (Vec2f){posX, posY};
    entities[numEntities].velocity = (Vec2f){0.5, 0};
    entities[numEntities].entityAnimations.currentAnimationIndex = WALK_RIGHT_ANIMATION;
    entities[numEntities].entityAnimations.currentFrame = 0;
    entities[numEntities].entityAnimations.elapsedTime = 0;
    entities[numEntities].entityAnimations.numAnimations = LAST_ANIMATION;
    entities[numEntities].entityAnimations.animations = &gSpriteAnimations[type * LAST_ANIMATION];
}

void createEnemy(int posX, int posY, int speed, EntityType type)
{
    if (numEntities <= MAX_GAME_ENTITIES)
    {
        initializeEnemyProperties(posX, posY, speed, type);
        ++numEntities;
    }
}

#endif