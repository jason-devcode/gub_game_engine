#ifndef SCREEN_API_H
#define SCREEN_API_H

#include <stdint.h> // For int types

// #include "timers.h"                                 // For UPDATE_TIMERS
#include "../engine_properties/depthbuffer.h"       // For depthbuffer
#include "../engine_properties/framebuffer.h"       // For framebuffer
#include "../engine_properties/screen_dimensions.h" // For framebufer

// Global variable for the clear screen color
static uint64_t gClearScreenColor = 0x0000000000000000LL;

/**
 * Macro to fill the screen with the clear screen color.
 */
#define clearScreen()                                                                                               \
    register uint64_t *endPixels = (uint64_t *)(&framebuffer[gCorrectPixelsWidth * gScreenHeight]);                 \
    for (register uint64_t *pixelsIterator = (uint64_t *)framebuffer; pixelsIterator < endPixels; ++pixelsIterator) \
        *pixelsIterator = gClearScreenColor;

/**
 * Macro to fill the screen with the clear screen color and clear the depth buffer.
 */
#define clearScreenDepth()                                                                                                                \
    register uint64_t *endPixels = (uint64_t *)(&framebuffer[gCorrectPixelsWidth * gScreenHeight - 1]);                                   \
    register double *pixelDepthIterator = depthbuffer;                                                                                    \
    for (register uint64_t *pixelsIterator = (uint64_t *)framebuffer; pixelsIterator < endPixels; ++pixelsIterator, ++pixelDepthIterator) \
    {                                                                                                                                     \
        *pixelsIterator = gClearScreenColor;                                                                                              \
        *pixelDepthIterator = 999999.0;                                                                                                   \
        *++pixelDepthIterator = 999999.0;                                                                                                 \
    }

/**
 * Macro to set the clear screen color.
 *
 * @param color The color value to set for clearing the screen.
 */
#define setClearScreenColor(color) \
    (gClearScreenColor = ((uint64_t)(color) & 0xFFFFFFFF) | ((uint64_t)(color) << 32))

#endif