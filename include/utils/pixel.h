#ifndef PIXEL_UTILS
#define PIXEL_UTILS

#include "../core/engine_properties/depthbuffer.h"
#include "../core/engine_properties/framebuffer.h"
#include "../core/engine_properties/screen_dimensions.h"

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

/**
 * Sets a pixel at (x, y) to the specified color if the given depth (Z) is less than the current depth at that pixel.
 *
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param Z The depth value to test against the current depth at the pixel.
 * @param color The color to set the pixel to if the depth test passes.
 */
void pixelDepthTest(int x, int y, double Z, unsigned int color)
{
    // Check if the coordinates are within screen bounds
    if (x < 0 || x >= gScreenWidth || y < 0 || y >= gScreenHeight)
        return;

    // Calculate the pixel index in the framebuffer
    register uint32_t pixelIndex = (y * gCorrectPixelsWidth) + x;

    // Get the pointer to the depth value at the pixel
    double *depthPixel = (double *)&depthbuffer[pixelIndex];

    // Set the pixel color if the new depth is less than the current depth
    if (Z < *depthPixel)
    {
        *depthPixel = Z;
        framebuffer[pixelIndex] = color;
    }
}

/**
 * A macro to calculate the index of a pixel in a 1D array representation of a 2D image.
 * This macro converts 2D coordinates (x, y) into a 1D index, assuming a row-major order
 * layout where each row of the image is stored consecutively in memory.
 *
 * @param x The x-coordinate of the pixel (column index).
 * @param y The y-coordinate of the pixel (row index).
 * @param width The width of the image or framebuffer in pixels.
 *
 * @return The index of the pixel in the 1D array.
 */
#define calculatePixelIndex(x, y, width) ((int)(((y) * width) + (x)))

#endif