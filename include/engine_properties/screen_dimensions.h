#ifndef SCREEN_DIMENSIONS_ENGINE_PROPS_H
#define SCREEN_DIMENSIONS_ENGINE_PROPS_H

#include <stdint.h>

// Global screen dimensions
uint32_t gScreenWidth = 0;       // Width of the screen in pixels
uint32_t gScreenHeight = 0;      // Height of the screen in pixels
uint32_t gScreenTotalPixels = 0; // Total pixels in the screen

#define gHalfScreenWidth (gScreenWidth >> 1)  // Half the screen width in pixels
#define gHalfScreenHeight (gScreenHeight >> 1)  // Half the screen height in pixels

// Corrected pixel width for handling SDL screen pitch
uint32_t gCorrectPixelsWidth = 0; // Number of pixels per row in framebuffer

#endif