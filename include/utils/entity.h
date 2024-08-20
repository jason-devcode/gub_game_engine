#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>

#include "vectorial_2D.h"
#include "sprite_animation.h"

typedef struct _tag_player_animations_
{
    SpriteAnimation *animations;
    int currentAnimationIndex;
    int numAnimations;
    int currentFrame;   // Current frame index
    double elapsedTime; // Time elapsed since the last frame change
} EntityAnimations;

typedef struct _tag_entity_
{
    EntityAnimations entityAnimations;
    Vec2f position;
    Vec2f velocity;
    double speed;
    uint32_t collisionLayer; // 0,1,2,3,4,5,6,7
} Entity;

static inline void updateEntityPosition(Entity *entity)
{
    entity->position = vec2f_add(entity->position, entity->velocity);
}

static inline void updateEntitiesPosition(Entity *entities, int numEntities)
{
    for (int entityIndex = 0; entityIndex < numEntities; ++entityIndex)
        updateEntityPosition(&entities[entityIndex]);
}

void updateEntityAnimations(EntityAnimations *entityAnimation)
{
    const SpriteAnimation *animation = &entityAnimation->animations[entityAnimation->currentAnimationIndex];

    if (entityAnimation == NULL || animation->frames == NULL)
        return;

    entityAnimation->elapsedTime += deltatime;
    if (entityAnimation->elapsedTime > animation->frameDuration)
    {
        entityAnimation->elapsedTime = 0;
        ++entityAnimation->currentFrame;
        entityAnimation->currentFrame %= animation->numFrames;
    }
}

void renderEntity(Entity *entity, int scale, uint32_t clearColorMask)
{
    EntityAnimations *currentEntityAnimation = &entity->entityAnimations;
    SpriteAnimation *currentAnimation = &currentEntityAnimation->animations[currentEntityAnimation->currentAnimationIndex];
    SpriteFrame *currentFrame = &currentAnimation->frames[currentEntityAnimation->currentFrame];

    drawScaledSubTextureWithClearColorMask(
        entity->position.x, entity->position.y,
        gBombermanSpritesheet->texture,
        currentFrame->x, currentFrame->y, currentFrame->w, currentFrame->h,
        currentFrame->w * scale, currentFrame->h * scale, clearColorMask);

    updateEntityAnimations(currentEntityAnimation);
}

void renderEntitiesCollection(Entity *entity, int numEntities, int scale, uint32_t clearColorMask)
{
    for (int entityIndex = 0; entityIndex < numEntities; ++entityIndex)
        renderEntity(&entity[entityIndex], scale, clearColorMask);
}

#endif