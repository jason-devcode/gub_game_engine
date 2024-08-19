#ifndef SPRITE_2D_ANIMATION_H
#define SPRITE_2D_ANIMATION_H

#include "sprite.h"
#include "../core/engine_properties/deltatime.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SpriteFrame
{
    int x;
    int y;
    int w;
    int h;
} SpriteFrame;

typedef struct SpriteAnimation
{
    SpriteFrame *frames;  // Animation frames
    int currentFrame;     // Current frame index
    int numFrames;        // Total number of frames in the animation
    double frameDuration; // Duration to show each frame ( in seconds )
    double elapsedTime;   // Time elapsed since the last frame change
} SpriteAnimation;

SpriteAnimation *createEmptySpriteAnimation()
{
    SpriteAnimation *animation = (SpriteAnimation *)malloc(sizeof(SpriteAnimation));

    if (animation == NULL)
    {
        fprintf(stderr, "ERROR: Could not allocate memory space for sprite animation\n");
        return NULL;
    }
    memset(animation, 0, sizeof(SpriteAnimation));
    return animation;
}

SpriteAnimation *createSequenceOfEmptySpriteAnimation(int numAnimations)
{
    SpriteAnimation *animations = (SpriteAnimation *)malloc(sizeof(SpriteAnimation[numAnimations]));

    if (animations == NULL)
    {
        fprintf(stderr, "ERROR: Could not allocate memory space for sequence of sprite animations\n");
        return NULL;
    }
    memset(animations, 0, sizeof(SpriteAnimation[numAnimations]));
    return animations;
}

SpriteFrame *createSequenceOfEmptyFrames(int numFrames)
{
    if (numFrames == 0)
    {
        fprintf(stderr, "ERROR: Num of frames should be greater than 0\n");
        return NULL;
    }
    SpriteFrame *frameSequence = (SpriteFrame *)malloc(sizeof(SpriteFrame[numFrames]));
    memset(frameSequence, 0, sizeof(SpriteFrame[numFrames]));
    return frameSequence;
}

void populateSpriteAnimation(SpriteAnimation *animation, int startCol, int startRow, int numColFrames, int numRowFrames, double frameDuration, Sprite *sprite)
{
    // Validate input parameters
    if (animation == NULL || sprite == NULL ||
        numColFrames <= 0 || numRowFrames <= 0 || frameDuration <= 0.0 ||
        startCol < 0 || startRow < 0 ||
        startCol >= sprite->numCols || startRow >= sprite->numRows)
    {
        return;
    }

    // Calculate the width and height of each frame
    int frameWidth = (int)((double)sprite->texture->width / sprite->numCols + 0.5);
    int frameHeight = (int)((double)sprite->texture->height / sprite->numRows + 0.5);

    // Calculate the starting position of the first frame
    int startX = frameWidth * startCol;
    int startY = frameHeight * startRow;

    // Initialize the animation properties
    animation->currentFrame = 0;
    animation->elapsedTime = 0.0;
    animation->frameDuration = frameDuration;
    animation->numFrames = numColFrames * numRowFrames;

    animation->frames = createSequenceOfEmptyFrames(animation->numFrames);
    if (animation->frames == NULL)
        return;

    // Populate the frames in the animation
    for (int row = 0; row < numRowFrames; ++row)
    {
        for (int col = 0; col < numColFrames; ++col)
        {
            int frameIndex = row * numColFrames + col;
            SpriteFrame *frame = &animation->frames[frameIndex];
            frame->x = startX + col * frameWidth;
            frame->y = startY + row * frameHeight;
            frame->w = frameWidth;
            frame->h = frameHeight;
        }
    }
}

SpriteAnimation *createSpriteAnimation(int startCol, int startRow, int numColFrames, int numRowFrames, double frameDuration, Sprite *sprite)
{
    // Validate input parameters
    if (
        sprite == NULL ||
        numColFrames == 0 ||
        numRowFrames == 0 ||
        frameDuration <= 0 ||
        startCol < 0 ||
        startRow < 0 ||
        !(startCol < sprite->numCols) ||
        !(startRow < sprite->numRows))
        return NULL;

    // Calculate the width and height of each frame
    int frameWidth = ((double)sprite->texture->width / sprite->numCols) + 0.5;
    int frameHeight = ((double)sprite->texture->height / sprite->numRows) + 0.5;

    // Calculate the starting position of the first frame
    int startX = frameWidth * startCol;
    int startY = frameHeight * startRow;

    // Create the sprite animation object
    SpriteAnimation *animation = createEmptySpriteAnimation();

    if (animation == NULL)
        return NULL;

    // Initialize the animation properties
    animation->currentFrame = 0;
    animation->elapsedTime = 0;
    animation->frameDuration = frameDuration;
    animation->numFrames = numColFrames * numRowFrames;
    animation->frames = createSequenceOfEmptyFrames(animation->numFrames);

    if (animation->frames == NULL)
    {
        free(animation);
        return NULL;
    }

    // Populate the frames in the animation
    for (int row = 0; row < numRowFrames; ++row)
    {
        for (int col = 0; col < numColFrames; ++col)
        {
            int frameIndex = row * numColFrames + col;
            SpriteFrame *frame = &animation->frames[frameIndex];
            frame->x = startX + col * frameWidth;
            frame->y = startY + row * frameHeight;
            frame->w = frameWidth;
            frame->h = frameHeight;
        }
    }

    return animation;
}

void updateSpriteAnimation(SpriteAnimation *animation)
{
    if (animation == NULL || animation->frames == NULL)
        return;

    animation->elapsedTime += deltatime;
    if (animation->elapsedTime > animation->frameDuration)
    {
        animation->elapsedTime = 0;
        ++animation->currentFrame;
        animation->currentFrame %= animation->numFrames;
    }
}

void releaseSpriteAnimationResources(SpriteAnimation *animation)
{
    if (animation == NULL)
        return;
    if (animation->frames)
        free(animation->frames);
    free(animation);
}

void releaseSequenceOfSpriteAnimationResources(SpriteAnimation **animations, int numAnimations)
{
    if (animations == NULL)
        return;

    for (int animationIndex = 0; animationIndex < numAnimations; ++animationIndex)
        if (animations[animationIndex])
            releaseSpriteAnimationResources(animations[animationIndex]);
}

#endif