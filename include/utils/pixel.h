#ifndef PIXEL_UTILS
#define PIXEL_UTILS

#include "../engine_properties/framebuffer.h"
#include "../engine_properties/screen_dimensions.h"

/**
 * Sets a pixel at (x, y) to the specified color.
 *
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color to set the pixel to.
 */
void pixel(int x, int y, unsigned int color)
{
    // Check if the coordinates are within screen bounds
    if (x < 0 || x >= gScreenWidth || y < 0 || y >= gScreenHeight)
        return;

    // Calculate the pixel index in the framebuffer
    register uint32_t pixelIndex = (y * gCorrectPixelsWidth) + x;

    // Set the pixel color
    framebuffer[pixelIndex] = color;
}

#endif