#ifndef GAME_EVENTS_SCRIPT_H
#define GAME_EVENTS_SCRIPT_H

#include "player.h"
#include "animations.h"

#include "../include/utils/keyboard.h"
#include "../include/core/engine_properties/deltatime.h"

void onMovePlayerLeft()
{
    player->entityAnimations.currentAnimationIndex = WALK_LEFT_ANIMATION;
    player->position.x -= player->speed * deltatime * 0.001;
}

void onMovePlayerRight()
{
    player->entityAnimations.currentAnimationIndex = WALK_RIGHT_ANIMATION;
    player->position.x += player->speed * deltatime * 0.001;
}

void onMovePlayerTop()
{
    player->entityAnimations.currentAnimationIndex = WALK_TOP_ANIMATION;
    player->position.y -= player->speed * deltatime * 0.001;
}

void onMovePlayerBottom()
{
    player->entityAnimations.currentAnimationIndex = WALK_BOTTOM_ANIMATION;
    player->position.y += player->speed * deltatime * 0.001;
}

void onIdleLeftPlayerState()
{
    player->entityAnimations.currentAnimationIndex = IDLE_LEFT_ANIMATION;
    player->entityAnimations.currentFrame = 0;
    player->entityAnimations.elapsedTime = 0;
}

void onIdleRightPlayerState()
{
    player->entityAnimations.currentAnimationIndex = IDLE_RIGHT_ANIMATION;
    player->entityAnimations.currentFrame = 0;
    player->entityAnimations.elapsedTime = 0;
}

void onIdleTopPlayerState()
{
    player->entityAnimations.currentAnimationIndex = IDLE_TOP_ANIMATION;
    player->entityAnimations.currentFrame = 0;
    player->entityAnimations.elapsedTime = 0;
}

void onIdleBottomPlayerState()
{
    player->entityAnimations.currentAnimationIndex = IDLE_BOTTOM_ANIMATION;
    player->entityAnimations.currentFrame = 0;
    player->entityAnimations.elapsedTime = 0;
}

void initializeGameEvents()
{
    addKeyPressEventListener(GUB_KEY_a, onMovePlayerLeft);
    addKeyPressEventListener(GUB_KEY_d, onMovePlayerRight);

    addKeyPressEventListener(GUB_KEY_w, onMovePlayerTop);
    addKeyPressEventListener(GUB_KEY_s, onMovePlayerBottom);

    addKeyReleaseEventListener(GUB_KEY_a, onIdleLeftPlayerState);
    addKeyReleaseEventListener(GUB_KEY_d, onIdleRightPlayerState);

    addKeyReleaseEventListener(GUB_KEY_w, onIdleTopPlayerState);
    addKeyReleaseEventListener(GUB_KEY_s, onIdleBottomPlayerState);
}

#endif