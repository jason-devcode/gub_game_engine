#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "entities.h"
#include "sprites.h"

typedef enum
{
    WALK_LEFT_ANIMATION,
    WALK_RIGHT_ANIMATION,
    WALK_TOP_ANIMATION,
    WALK_BOTTOM_ANIMATION,
    IDLE_LEFT_ANIMATION,
    IDLE_RIGHT_ANIMATION,
    IDLE_TOP_ANIMATION,
    IDLE_BOTTOM_ANIMATION,
    DEATH_ANIMATION,
    LAST_ANIMATION
} AnimationType;

SpriteAnimation gSpriteAnimations[LAST_ENTITY_TYPE * LAST_ANIMATION];

void initializePlayerAnimations()
{
    double frameDuration = 1.0 / 60.0 * 6.0;

    player->entityAnimations.animations = &gSpriteAnimations[PLAYER * LAST_ANIMATION];
    player->entityAnimations.currentAnimationIndex = IDLE_RIGHT_ANIMATION;
    player->entityAnimations.numAnimations = LAST_ANIMATION;

    populateSpriteAnimation(&gSpriteAnimations[PLAYER * LAST_ANIMATION + WALK_LEFT_ANIMATION], 0, 0, 3, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&gSpriteAnimations[PLAYER * LAST_ANIMATION + WALK_RIGHT_ANIMATION], 0, 1, 3, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&gSpriteAnimations[PLAYER * LAST_ANIMATION + WALK_BOTTOM_ANIMATION], 3, 0, 3, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&gSpriteAnimations[PLAYER * LAST_ANIMATION + WALK_TOP_ANIMATION], 3, 1, 3, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&gSpriteAnimations[PLAYER * LAST_ANIMATION + IDLE_LEFT_ANIMATION], 1, 0, 1, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&gSpriteAnimations[PLAYER * LAST_ANIMATION + IDLE_RIGHT_ANIMATION], 1, 1, 1, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&gSpriteAnimations[PLAYER * LAST_ANIMATION + IDLE_BOTTOM_ANIMATION], 4, 0, 1, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&gSpriteAnimations[PLAYER * LAST_ANIMATION + IDLE_TOP_ANIMATION], 4, 1, 1, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&gSpriteAnimations[PLAYER * LAST_ANIMATION + DEATH_ANIMATION], 0, 2, 7, 1, frameDuration, gBombermanSpritesheet);
}

void initializeEnemyAnimations(EntityType type)
{
    double frameDuration = 1.0 / 60.0 * 10.0;

    int rowAnimation = (type - 1) + 15;

    populateSpriteAnimation(&gSpriteAnimations[type * LAST_ANIMATION + WALK_RIGHT_ANIMATION], 0, rowAnimation, 3, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&gSpriteAnimations[type * LAST_ANIMATION + WALK_LEFT_ANIMATION], 3, rowAnimation, 3, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&gSpriteAnimations[type * LAST_ANIMATION + IDLE_RIGHT_ANIMATION], 1, rowAnimation, 1, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&gSpriteAnimations[type * LAST_ANIMATION + IDLE_LEFT_ANIMATION], 4, rowAnimation, 1, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&gSpriteAnimations[type * LAST_ANIMATION + DEATH_ANIMATION], 0, 2, 7, 1, frameDuration, gBombermanSpritesheet);
}

void initializeAnimations()
{
    initializePlayerAnimations();
    initializeEnemyAnimations(ENEMY_BALLON);
    initializeEnemyAnimations(ENEMY_ONIL);
    initializeEnemyAnimations(ENEMY_DALL);
    initializeEnemyAnimations(ENEMY_MINVO);
    initializeEnemyAnimations(ENEMY_OVAPI);
    initializeEnemyAnimations(ENEMY_KONDORIA);
    initializeEnemyAnimations(ENEMY_PARSE);
    initializeEnemyAnimations(ENEMY_PONTAN);
}

void releaseAnimations()
{
    for (int animationsIndex = 0; animationsIndex < LAST_ENTITY_TYPE; ++animationsIndex)
        releaseSpriteAnimationResources(&gSpriteAnimations[animationsIndex], true);
}

#endif