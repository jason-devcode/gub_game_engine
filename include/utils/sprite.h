#ifndef SPRITE_H
#define SPRITE_H

#include "texture.h"
#include <stdlib.h>

typedef struct _tag_sprite_
{
    Texture *texture; // Can be a single sprite texture or a spritesheet
    int numCols;      // Number of Cols for spritesheet textures
    int numRows;      // Number of Rows for spritesheet textures
} Sprite;

Sprite *createEmptySprite()
{
    Sprite *out;
    out = (Sprite *)malloc(sizeof(Sprite));
    if (out == NULL)
    {
        fprintf(stderr, "ERROR: Could not allocate memory space to create sprite\n");
        return NULL;
    }
    out->numCols = 0;
    out->numRows = 0;
    out->texture = NULL;
    return out;
}

Sprite *loadSpriteFromTextureFile(const char *filename, int numCols, int numRows)
{
    if (filename == NULL)
        goto fail_to_load_sprite_from_file;

    Sprite *out = createEmptySprite();

    if (out == NULL)
        goto fail_to_load_sprite_from_file;

    out->texture = loadTextureFromImageFile(filename);

    if (out->texture == NULL)
        goto fail_to_load_sprite_from_file;

    out->numCols = numCols;
    out->numRows = numRows;

    return out;

fail_to_load_sprite_from_file:
    if (out)
        free(out);
    return NULL;
}

void releaseSpriteResources(Sprite *sprite)
{
    if (sprite == NULL)
        return;

    if (sprite->texture)
        releaseTextureResources(sprite->texture);

    sprite->numCols = 0;
    sprite->numRows = 0;

    free(sprite);
}

#endif