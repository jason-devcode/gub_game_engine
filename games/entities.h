#ifndef ENTITIES_H
#define ENTITIES_H

#include "../include/utils/entity.h"

typedef enum
{
    PLAYER,
    ENEMY_BALLON,
    ENEMY_ONIL,
    ENEMY_DALL,
    ENEMY_MINVO,
    ENEMY_OVAPI,
    ENEMY_KONDORIA,
    ENEMY_PARSE,
    ENEMY_PONTAN,
    LAST_ENTITY_TYPE
} EntityType;

#define MAX_GAME_ENTITIES 32

Entity entities[MAX_GAME_ENTITIES];

Entity *player = entities;

Entity *enemySlotFree;

int numEntities = 1;

int freeEntitySlot = 1;

static inline void renderEntities() { renderEntitiesCollection(entities, numEntities, 2, 0xFF388700); }

static inline void updateEntities()
{
    updateEntitiesPosition(entities, numEntities);
}

#endif