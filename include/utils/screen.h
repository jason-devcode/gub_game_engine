#ifndef SCREEN_UTILS_H
#define SCREEN_UTILS_H

#include <stdint.h> // For int types

#include <SDL/SDL_video.h> // For SDL_Flip

#include "timers.h"                                 // For UPDATE_TIMERS
#include "../engine_properties/depthbuffer.h"       // For depthbuffer
#include "../engine_properties/framebuffer.h"       // For framebuffer
#include "../engine_properties/engine_instance.h"   // For engine instance
#include "../engine_properties/screen_dimensions.h" // For framebufer

// Global variable for the clear screen color
static uint64_t gClearScreenColor = 0x0000000000000000LL;

/**
 * Initializes the SDL screen with the given width and height.
 *
 * @param screenWidth Width of the screen in pixels.
 * @param screenHeight Height of the screen in pixels.
 * @return Returns true if the screen is initialized successfully, false otherwise.
 */
bool initializeScreen(uint16_t screenWidth, uint16_t screenHeight)
{
    // Set the video mode with the given screen dimensions and 32-bit color depth
    gInstance.screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_SWSURFACE);
    if (gInstance.screen == NULL)
    {
        // Print an error message if screen initialization fails
        fprintf(stderr, "Cannot set video mode: %s\n", SDL_GetError());
        return false;
    }

    // Initialize global screen properties
    gScreenWidth = screenWidth;
    gScreenHeight = screenHeight;

    // Correct the pixel width calculation based on screen pitch
    gCorrectPixelsWidth = gInstance.screen->pitch >> 2; // >> 2 is equivalent to / 4

    gScreenTotalPixels = gCorrectPixelsWidth * screenHeight;

    // Set framebuffer pointer to the screen’s pixel data
    framebuffer = (uint32_t *)gInstance.screen->pixels;

    // Allocate memory for the depth buffer
    depthbuffer = (double *)malloc(sizeof(double[gScreenTotalPixels]));

    return true;
}

/**
 * Macro to update the screen with the current framebuffer contents.
 */
#define drawScreen()            \
    SDL_Flip(gInstance.screen); \
    UPDATE_TIMERS()

/**
 * Macro to fill the screen with the clear screen color.
 */
#define clearScreen()                                                                                               \
    register uint64_t *endPixels = (uint64_t *)(&framebuffer[gScreenTotalPixels - 1]);                              \
    for (register uint64_t *pixelsIterator = (uint64_t *)framebuffer; pixelsIterator < endPixels; ++pixelsIterator) \
        *pixelsIterator = gClearScreenColor;

/**
 * Macro to fill the screen with the clear screen color and clear the depth buffer.
 */
#define clearScreenDepth()                                                                                                                \
    register uint64_t *endPixels = (uint64_t *)(&framebuffer[gScreenTotalPixels - 1]);                                                    \
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